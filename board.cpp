#include "board.h"
#include <QtGlobal>

Board::Board(int size):
    mSize(static_cast<size_t>(size))
{
    for(size_t i=0; i<mSize; ++i)
    {
        mPieces.emplace_back();

        for(size_t j=0; j<mSize; ++j)
        {
            mPieces[i].emplace_back(Piece::ENone);
        }
    }
}

int Board::size() const
{
    return static_cast<int>(mSize);
}

Piece Board::piece(int x, int y) const
{
    auto xPos = static_cast<size_t>(x);
    auto yPos = static_cast<size_t>(y);

    Q_ASSERT(xPos < mSize);
    Q_ASSERT(yPos < mSize);

    return mPieces[xPos][yPos];
}

void Board::setPiece(int x, int y, Piece piece)
{
    auto xPos = static_cast<size_t>(x);
    auto yPos = static_cast<size_t>(y);

    Q_ASSERT(xPos < mSize);
    Q_ASSERT(yPos < mSize);

    mPieces[xPos][yPos] = piece;
}
