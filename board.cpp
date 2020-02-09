#include "board.h"
#include "square.h"

Board::Board(int size)
{
    for(auto i = 0; i < size; ++i)
    {
        mPieces.emplace_back();

        for(auto j = 0; j < size; ++j)
        {
            mPieces.back().emplace_back(Piece::ENone);
        }
    }
}

int Board::size() const
{
    return mPieces.size();
}

Piece Board::piece(const Square &square) const
{
    auto piece = Piece::ENone;

    if(square.isValid(*this))
    {
        auto x = static_cast<size_t>(square.x());
        auto y = static_cast<size_t>(square.y());

        piece = mPieces[x][y];
    }
    else
    {
        Q_ASSERT(false);
    }

    return piece;
}

void Board::setPiece(const Square &square, Piece piece)
{
    if(square.isValid(*this))
    {
        auto x = static_cast<size_t>(square.x());
        auto y = static_cast<size_t>(square.y());

        mPieces[x][y] = piece;
    }
    else
    {
        Q_ASSERT(false);
    }
}


