#include "game.h"

Game::Game():
    mBoard(8),
    mEnPassantX(-1),
    mUndoCount(0)
{
    resetPieces();
}

void Game::doMove(Move const& move)
{
    mEnPassantX = -1;

    while(mUndoCount > 0)
    {
        mMoves.pop_back();
        --mUndoCount;
    }
    mMoves.push_back(move);

    auto piece = mBoard.piece(move.mOriginX, move.mOriginY);
    auto captured = mBoard.piece(move.mDestinationX, move.mDestinationY);

    auto pawnMove = (piece == Piece::EWhitePawn) || (piece == Piece::EBlackPawn);
    if(pawnMove)
    {
        auto pawnAdvancingTwoSquares = std::abs(move.mOriginY - move.mDestinationY) > 1;
        if(pawnAdvancingTwoSquares)
        {
            mEnPassantX = move.mDestinationX;
        }

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

void Game::undoMove()
{
    auto index = (mMoves.size() - 1) - mUndoCount;
    Q_ASSERT(index >= 0);
    Q_ASSERT(index < mMoves.size());

    auto move = mMoves[index];

    auto piece = mBoard.piece(move.mDestinationX, move.mDestinationY);
    auto captured = move.mCaptured;

    mBoard.setPiece(move.mDestinationX, move.mDestinationY, captured);
    mBoard.setPiece(move.mOriginX, move.mOriginY, piece);

    emit pieceMoved(move.mDestinationX, move.mDestinationY, move.mOriginX, move.mOriginY);
    if(captured != Piece::ENone)
    {
        emit pieceAdded(move.mDestinationX, move.mDestinationY, captured);
    }

    ++mUndoCount;
}

void Game::redoMove()
{
    auto index = mMoves.size() - mUndoCount;

    Q_ASSERT(index < mMoves.size());

    auto move = mMoves[index];
    auto piece = mBoard.piece(move.mOriginX, move.mOriginY);
    auto captured = mBoard.piece(move.mDestinationX, move.mDestinationY);

    auto pawnMove = (piece == Piece::EWhitePawn) || (piece == Piece::EBlackPawn);
    if(pawnMove)
    {
        auto pawnAdvancingTwoSquares = std::abs(move.mOriginY - move.mDestinationY) > 1;
        if(pawnAdvancingTwoSquares)
        {
            mEnPassantX = move.mDestinationX;
        }

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

    --mUndoCount;
}

void Game::newGame()
{
    mMoves.clear();
    mUndoCount = 0;

    resetPieces();

    emit piecesReset();
}

Board Game::getBoard() const
{
    return mBoard;
}

std::vector<Move> Game::getMovesPlayed() const
{
    return mMoves;
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

                if(y == mBoard.size() - 2)
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
            }
            if(x < mBoard.size() - 1)
            {
                if(PieceUtils::isBlack(mBoard.piece(x+1, y-1)))
                {
                    moves.emplace_back(x, y, x+1, y-1, mBoard.piece(x+1, y-1));
                }
            }

            auto enpassantAvailable = mEnPassantX >= 0;
            if(enpassantAvailable)
            {
                if(y == 3)
                {
                    if(x+1 == mEnPassantX)
                    {
                        moves.emplace_back(x, y, x+1, y-1, Piece::EBlackPawn);
                    }
                    else if(x-1 == mEnPassantX)
                    {
                        moves.emplace_back(x, y, x-1, y-1, Piece::EBlackPawn);
                    }
                }
            }
        }


    }
    else if(piece == Piece::EBlackPawn && sideToMove() == Color::EBlack)
    {
        if(y + 1 < mBoard.size())
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
            }
            if(x < mBoard.size() - 1)
            {
                if(PieceUtils::isWhite(mBoard.piece(x+1, y+1)))
                {
                    moves.emplace_back(x, y, x+1, y+1, mBoard.piece(x+1, y+1));
                }
            }

            auto enpassantAvailable = mEnPassantX >= 0;
            if(enpassantAvailable)
            {
                if(y == mBoard.size() - 4)
                {
                    if(x+1 == mEnPassantX)
                    {
                        moves.emplace_back(x, y, x+1, y+1, Piece::EWhitePawn);
                    }
                    else if(x-1 == mEnPassantX)
                    {
                        moves.emplace_back(x, y, x-1, y+1, Piece::EWhitePawn);
                    }
                }
            }
        }
    }

    return moves;
}

void Game::resetPieces()
{
    mBoard = Board(8);

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
}

Color Game::sideToMove() const
{
    return ((mMoves.size() - mUndoCount) % 2 == 0) ? Color::EWhite : Color::EBlack;
}

size_t Game::undoCount() const
{
    return mUndoCount;
}
