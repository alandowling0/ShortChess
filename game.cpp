#include "game.h"
#include "position.h"
#include "movegeneration.h"

Game::Game(Board& board) :
    mBoard(board)
{
    resetPieces();
}

void Game::playMove(Move const& move)
{
    mMovesUndone.clear();

    doMove(move);
}

void Game::takebackMove()
{
    if(mMoves.size() > 0)
    {
        auto move = mMoves.back();
        mMoves.pop_back();

        undoMove(move);
    }
    else
    {
        Q_ASSERT(false);
    }
}

void Game::replayMove()
{
    if(mMovesUndone.size() > 0)
    {
        auto move = mMovesUndone.back();
        mMovesUndone.pop_back();

        doMove(move);
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

std::vector<Move> Game::getMoves(Square const& origin)
{
    std::vector<Move> moves;

    auto position = mBoard.position();

    // label a pawn as available en passant if the previous move was a pawn moving 2 squares
    if(mMoves.size() > 0)
    {
        auto previousMove = mMoves.back();

        auto wasPawnMove =
            previousMove.piece() == Piece::EWhitePawn ||
            previousMove.piece() == Piece::EBlackPawn;

        auto movedTwoSquares = std::abs(previousMove.origin().y() - previousMove.destination().y()) == 2;

        if(wasPawnMove && movedTwoSquares)
        {
            position.setAvailableEnPassant(previousMove.destination());
        }
    }

    moves = MoveGeneration::getMoves(position, origin);

    return moves;
}

std::vector<Move> Game::getMovesPlayed() const
{
    return mMoves;
}

std::vector<Move> Game::getMovesUndone() const
{
    return mMovesUndone;
}

Color Game::sideToMove() const
{
    return (mMoves.size() % 2 == 0) ? Color::EWhite : Color::EBlack;
}

void Game::doMove(Move const& move)
{
    // remove the piece being captured if any
    if(move.captured() != Piece::ENone)
    {
        auto capturedSquare = move.destination();
        if(move.enPassant())
        {
            capturedSquare = Square{move.destination().x(), move.origin().y()};
        }

        mBoard.setPiece(capturedSquare, Piece::ENone);
    }

    // move the piece being moved
    mBoard.movePiece(move.origin(), move.destination());

    mMoves.push_back(move);
}

void Game::undoMove(Move const& move)
{
    mBoard.movePiece(move.destination(), move.origin());

    auto captured = move.captured();
    if(captured != Piece::ENone)
    {
        auto capturedPieceX = move.destination().x();
        auto capturedPieceY = move.destination().y();

        if(move.enPassant())
        {
            capturedPieceY = move.origin().y();
        }

        mBoard.setPiece(Square{capturedPieceX, capturedPieceY}, captured);
    }

    mMovesUndone.emplace_back(move);
}

void Game::resetPieces()
{
    mBoard.clear();

    mBoard.setPiece(Square{0, 6}, Piece::EWhitePawn);
    mBoard.setPiece(Square{1, 6}, Piece::EWhitePawn);
    mBoard.setPiece(Square{2, 6}, Piece::EWhitePawn);
    mBoard.setPiece(Square{3, 6}, Piece::EWhitePawn);
    mBoard.setPiece(Square{4, 6}, Piece::EWhitePawn);
    mBoard.setPiece(Square{5, 6}, Piece::EWhitePawn);
    mBoard.setPiece(Square{6, 6}, Piece::EWhitePawn);
    mBoard.setPiece(Square{7, 6}, Piece::EWhitePawn);

    mBoard.setPiece(Square{4, 7}, Piece::EWhiteKing);

    mBoard.setPiece(Square{0, 1}, Piece::EBlackPawn);
    mBoard.setPiece(Square{1, 1}, Piece::EBlackPawn);
    mBoard.setPiece(Square{2, 1}, Piece::EBlackPawn);
    mBoard.setPiece(Square{3, 1}, Piece::EBlackPawn);
    mBoard.setPiece(Square{4, 1}, Piece::EBlackPawn);
    mBoard.setPiece(Square{5, 1}, Piece::EBlackPawn);
    mBoard.setPiece(Square{6, 1}, Piece::EBlackPawn);
    mBoard.setPiece(Square{7, 1}, Piece::EBlackPawn);

    mBoard.setPiece(Square{4, 0}, Piece::EBlackKing);
}



