#include "game.h"

Game::Game()
{
    resetPieces();
}

void Game::playMove(Move const& move)
{
    mMovesUndone.clear();

    doMove(move);
}

void Game::undoMove()
{
    if(mMoves.size() > 0)
    {
        auto move = mMoves.back();
        mMoves.pop_back();

        auto piece = mBoard.piece(move.mDestinationX, move.mDestinationY);
        auto captured = move.mCaptured;

        mBoard.setPiece(move.mDestinationX, move.mDestinationY, captured);
        mBoard.setPiece(move.mOriginX, move.mOriginY, piece);

        emit pieceMoved(move.mDestinationX, move.mDestinationY, move.mOriginX, move.mOriginY);

        if(captured != Piece::ENone)
        {
            emit pieceAdded(move.mDestinationX, move.mDestinationY, captured);
        }

        mMovesUndone.emplace_back(move);
    }
    else
    {
        Q_ASSERT(false);
    }
}

void Game::redoMove()
{
    if(mMovesUndone.size() > 0)
    {
        doMove(mMovesUndone.back());

        mMovesUndone.pop_back();
    }
    else
    {
        Q_ASSERT(false);
    }
}

void Game::newGame()
{
    mMoves.clear();
    mMovesUndone.clear();

    resetPieces();
}

Board<8, 8> Game::getBoard() const
{
    return mBoard;
}

std::vector<Move> Game::getMovesPlayed() const
{
    return mMoves;
}

std::vector<Move> Game::getMovesUndone() const
{
    return mMovesUndone;
}

std::vector<Move> Game::getLegalMoves(int x, int y) const
{
    std::vector<Move> moves;

    auto piece = mBoard.piece(x, y);

    if(piece == Piece::EWhitePawn && sideToMove() == Color::EWhite)
    {
        if(y >= 1)
        {
            if(mBoard.piece(x, y-1) == Piece::ENone)
            {
                moves.emplace_back(x, y, x, y-1);

                if(y == mBoard.rows() - 2)
                {
                    if(mBoard.piece(x, y-2) == Piece::ENone)
                    {
                        moves.emplace_back(x, y, x, y-2);
                    }
                }
            }
            if(x > 0)
            {
                if(PieceUtils::isBlack(mBoard.piece(x-1, y-1)))
                {
                    moves.emplace_back(x, y, x-1, y-1, mBoard.piece(x-1, y-1));
                }

                auto canTakeEp = y == 3
                                && (mBoard.piece(x-1, y) == Piece::EBlackPawn)
                                && (mMoves.back().mDestinationX == x-1)
                                && (mMoves.back().mDestinationY == y)
                                && (mMoves.back().mOriginX == x-1)
                                && (mMoves.back().mOriginY == y-2);
                if(canTakeEp)
                {
                    moves.emplace_back(x, y, x-1, y-1, Piece::EBlackPawn);
                }
            }
            if(x < mBoard.columns() - 1)
            {
                if(PieceUtils::isBlack(mBoard.piece(x+1, y-1)))
                {
                    moves.emplace_back(x, y, x+1, y-1, mBoard.piece(x+1, y-1));
                }

                auto canTakeEp = y == 3
                                && (mBoard.piece(x+1, y) == Piece::EBlackPawn)
                                && (mMoves.back().mDestinationX == x+1)
                                && (mMoves.back().mDestinationY == y)
                                && (mMoves.back().mOriginX == x+1)
                                && (mMoves.back().mOriginY == y-2);
                if(canTakeEp)
                {
                    moves.emplace_back(x, y, x+1, y-1, Piece::EBlackPawn);
                }
            }
        }
    }
    else if(piece == Piece::EBlackPawn && sideToMove() == Color::EBlack)
    {
        if(y + 1 < mBoard.rows())
        {
            if(mBoard.piece(x, y+1) == Piece::ENone)
            {
                moves.emplace_back(x, y, x, y+1);

                if(y == 1)
                {
                    if(mBoard.piece(x, y+2) == Piece::ENone)
                    {
                        moves.emplace_back(x, y, x, y+2);
                    }
                }
            }
            if(x > 0)
            {
                if(PieceUtils::isWhite(mBoard.piece(x-1, y+1)))
                {
                    moves.emplace_back(x, y, x-1, y+1, mBoard.piece(x-1, y+1));
                }

                auto canTakeEp = y == mBoard.rows() - 4
                                && (mBoard.piece(x-1, y) == Piece::EWhitePawn)
                                && (mMoves.back().mDestinationX == x-1)
                                && (mMoves.back().mDestinationY == y)
                                && (mMoves.back().mOriginX == x-1)
                                && (mMoves.back().mOriginY == y+2);
                if(canTakeEp)
                {
                    moves.emplace_back(x, y, x-1, y+1, Piece::EWhitePawn);
                }
            }
            if(x < mBoard.columns() - 1)
            {
                if(PieceUtils::isWhite(mBoard.piece(x+1, y+1)))
                {
                    moves.emplace_back(x, y, x+1, y+1, mBoard.piece(x+1, y+1));
                }

                auto canTakeEp = y == mBoard.rows() - 4
                                && (mBoard.piece(x+1, y) == Piece::EWhitePawn)
                                && (mMoves.back().mDestinationX == x+1)
                                && (mMoves.back().mDestinationY == y)
                                && (mMoves.back().mOriginX == x+1)
                                && (mMoves.back().mOriginY == y+2);
                if(canTakeEp)
                {
                    moves.emplace_back(x, y, x+1, y+1, Piece::EWhitePawn);
                }
            }
        }
    }

    return moves;
}

Color Game::sideToMove() const
{
    return (mMoves.size() % 2 == 0) ? Color::EWhite : Color::EBlack;
}

void Game::doMove(Move const& move)
{
    mMoves.push_back(move);
    auto piece = mBoard.piece(move.mOriginX, move.mOriginY);
    auto captured = mBoard.piece(move.mDestinationX, move.mDestinationY);

    auto pawnMove = (piece == Piece::EWhitePawn) || (piece == Piece::EBlackPawn);
    if(pawnMove)
    {
        auto enPassant = (move.mDestinationX != move.mOriginX) && (captured == Piece::ENone);
        if(enPassant)
        {
            mBoard.setPiece(move.mDestinationX, move.mOriginY, Piece::ENone);
            emit pieceRemoved(move.mDestinationX, move.mOriginY);
        }
    }

    if(captured != Piece::ENone)
    {
        emit pieceRemoved(move.mDestinationX, move.mDestinationY);
    }

    mBoard.setPiece(move.mDestinationX, move.mDestinationY, piece);
    mBoard.setPiece(move.mOriginX, move.mOriginY, Piece::ENone);
    emit pieceMoved(move.mOriginX, move.mOriginY, move.mDestinationX, move.mDestinationY);
}

void Game::resetPieces()
{
    mBoard = Board<8, 8>();

    mBoard.setPiece(0, 6, Piece::EWhitePawn);
    mBoard.setPiece(1, 6, Piece::EWhitePawn);
    mBoard.setPiece(2, 6, Piece::EWhitePawn);
    mBoard.setPiece(3, 6, Piece::EWhitePawn);
    mBoard.setPiece(4, 6, Piece::EWhitePawn);
    mBoard.setPiece(5, 6, Piece::EWhitePawn);
    mBoard.setPiece(6, 6, Piece::EWhitePawn);
    mBoard.setPiece(7, 6, Piece::EWhitePawn);

    mBoard.setPiece(0, 1, Piece::EBlackPawn);
    mBoard.setPiece(1, 1, Piece::EBlackPawn);
    mBoard.setPiece(2, 1, Piece::EBlackPawn);
    mBoard.setPiece(3, 1, Piece::EBlackPawn);
    mBoard.setPiece(4, 1, Piece::EBlackPawn);
    mBoard.setPiece(5, 1, Piece::EBlackPawn);
    mBoard.setPiece(6, 1, Piece::EBlackPawn);
    mBoard.setPiece(7, 1, Piece::EBlackPawn);

    emit piecesReset();
}

