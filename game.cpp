#include "game.h"

Game::Game()
{
    resetPieces();
}

void Game::doMove(Move const& aMove)
{
    auto originX = static_cast<size_t>(aMove.mOriginX);
    auto originY = static_cast<size_t>(aMove.mOriginY);
    auto destinationX = static_cast<size_t>(aMove.mDestinationX);
    auto destinationY = static_cast<size_t>(aMove.mDestinationY);

    mBoard[destinationX][destinationY] = mBoard[originX][originY];
    mBoard[originX][originY] = Piece::ENone;
    emit pieceRemoved(static_cast<int>(destinationX), static_cast<int>(destinationY));

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

std::vector<std::vector<Piece>> Game::getBoard() const
{
    return mBoard;
}

std::vector<Move> Game::getMovesPlayed() const
{
    return mMoves;
}

std::vector<Move> Game::getLegalMoves(int originX, int originY) const
{
    std::vector<Move> moves;

    auto x = static_cast<size_t>(originX);
    auto y = static_cast<size_t>(originY);

    if(x < mBoard.size() && y < mBoard[x].size())
    {
        auto& piece = mBoard[x][y];

        if(piece == Piece::EWhitePawn)
        {
            if(sideToMove() == Color::EWhite)
            {
                if(y >= 1)
                {
                    if(mBoard[x][y-1] == Piece::ENone)
                    {
                        moves.emplace_back(x, y, x, y-1);

                        if(y == mBoard[x].size() - 2)
                        {
                            if(mBoard[x][y-2] == Piece::ENone)
                            {
                                moves.emplace_back(x, y, x, y-2);
                            }
                        }
                    }
                    if(x > 0)
                    {
                        if(PieceUtils::isBlack(mBoard[x-1][y-1]))
                        {
                            moves.emplace_back(x, y, x-1, y-1);
                        }
                    }
                    if(x < mBoard.size() - 1)
                    {
                        if(PieceUtils::isBlack(mBoard[x+1][y-1]))
                        {
                            moves.emplace_back(x, y, x+1, y-1);
                        }
                    }
                }
            }
        }
        else if(piece == Piece::EBlackPawn)
        {
            if(sideToMove() == Color::EBlack)
            {
                if(y + 1 < mBoard[x].size())
                {
                    if(mBoard[x][y+1] == Piece::ENone)
                    {
                        moves.emplace_back(x, y, x, y+1);

                        if(y == 1)
                        {
                            if(mBoard[x][y+2] == Piece::ENone)
                            {
                                moves.emplace_back(x, y, x, y+2);
                            }
                        }
                    }
                    if(x > 0)
                    {
                        if(PieceUtils::isWhite(mBoard[x-1][y+1]))
                        {
                            moves.emplace_back(x, y, x-1, y+1);
                        }
                    }
                    if(x < mBoard.size() - 1)
                    {
                        if(PieceUtils::isWhite(mBoard[x+1][y+1]))
                        {
                            moves.emplace_back(x, y, x+1, y+1);
                        }
                    }
                }
            }
        }
    }

    return moves;
}

void Game::resetPieces()
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
}

Color Game::sideToMove() const
{
    return (mMoves.size() % 2 == 0) ? Color::EWhite : Color::EBlack;
}
