#include "game.h"

Game::Game():
    mBoard(8)
{
    resetPieces();
}

void Game::doMove(Move const& aMove)
{
    mBoard.setPiece(aMove.mDestinationX, aMove.mDestinationY, mBoard.piece(aMove.mOriginX, aMove.mOriginY));
    mBoard.setPiece(aMove.mOriginX, aMove.mOriginY, Piece::ENone);
    emit pieceRemoved(aMove.mDestinationX, aMove.mDestinationY);

    mMoves.push_back(aMove);

    emit pieceMoved(aMove.mOriginX, aMove.mOriginY, aMove.mDestinationX, aMove.mDestinationY);
}

void Game::undoMove()
{

}

void Game::redoMove()
{

}

void Game::newGame()
{
    mMoves.clear();

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
                    moves.emplace_back(x, y, x-1, y-1);
                }
            }
            if(x < mBoard.size() - 1)
            {
                if(PieceUtils::isBlack(mBoard.piece(x+1, y-1)))
                {
                    moves.emplace_back(x, y, x+1, y-1);
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
                    moves.emplace_back(x, y, x-1, y+1);
                }
            }
            if(x < mBoard.size() - 1)
            {
                if(PieceUtils::isWhite(mBoard.piece(x+1, y+1)))
                {
                    moves.emplace_back(x, y, x+1, y+1);
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
    return (mMoves.size() % 2 == 0) ? Color::EWhite : Color::EBlack;
}
