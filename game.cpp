#include "game.h"

Game::Game()
{
}

void Game::newGame()
{
    mBoard.clear();

    for(size_t i=0; i<8; ++i)
    {
        mBoard.emplace_back();

        for(size_t j=0; j<8; ++j)
        {
            mBoard[i].emplace_back(Piece::ENone);
        }
    }

    mBoard[0][1] = Piece::EBlackPawn;
    mBoard[1][1] = Piece::EBlackPawn;
    mBoard[2][1] = Piece::EBlackPawn;
    mBoard[3][1] = Piece::EBlackPawn;
    mBoard[4][1] = Piece::EBlackPawn;
    mBoard[5][1] = Piece::EBlackPawn;
    mBoard[6][1] = Piece::EBlackPawn;
    mBoard[7][1] = Piece::EBlackPawn;

    mBoard[0][6] = Piece::EWhitePawn;
    mBoard[1][6] = Piece::EWhitePawn;
    mBoard[2][6] = Piece::EWhitePawn;
    mBoard[3][6] = Piece::EWhitePawn;
    mBoard[4][6] = Piece::EWhitePawn;
    mBoard[5][6] = Piece::EWhitePawn;
    mBoard[6][6] = Piece::EWhitePawn;
    mBoard[7][6] = Piece::EWhitePawn;

    emit alan();
}

void Game::playMove(Move const& aMove)
{
    mBoard[aMove.mDestinationX][aMove.mDestinationY] = mBoard[aMove.mOriginX][aMove.mOriginY];
    mBoard[aMove.mOriginX][aMove.mOriginY] = Piece::ENone;
    mMoves.push_back(aMove);

    emit pieceMoved(aMove.mOriginX, aMove.mOriginY, aMove.mDestinationX, aMove.mDestinationY);
}

void Game::undoMove()
{

}

void Game::redoMove()
{

}

std::vector<std::vector<Piece>> Game::getBoard() const
{
    return mBoard;
}

std::vector<Move> Game::getMovesPlayed() const
{
    return mMoves;
}

std::vector<Move> Game::getLegalMoves(size_t x, size_t y) const
{
    std::vector<Move> moves;

    auto& piece = mBoard[x][y];

    if(piece == Piece::EWhitePawn)
    {
        if(sideToMove() == Color::EWhite)
        {
            if(y >= 1)
            {
                moves.emplace_back(x, y, x, y-1);
            }
        }
    }
    else if(piece == Piece::EBlackPawn)
    {
        if(sideToMove() == Color::EBlack)
        {
            if(y + 1 < 8)
            {
                moves.emplace_back(x, y, x, y+1);
            }
        }
    }

    return moves;
}

Color Game::sideToMove() const
{
    return (mMoves.size() % 2 == 0) ? Color::EWhite : Color::EBlack;
}
