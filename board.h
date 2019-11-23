#pragma once

#include <array>
#include "piece.h"

template <int R, int C>
class Board
{
public:
    Board()
    {
        for(auto & row : mPieces)
        {
            for(auto & piece : row)
            {
                piece = Piece::ENone;
            }
        }
    }

    int rows() const
    {
        return R;
    }

    int columns() const
    {
        return C;
    }

    Piece piece(int x, int y) const
    {
        return mPieces[x][y];
    }

    void setPiece(int x, int y, Piece piece)
    {
        mPieces[x][y] = piece;
    }

private:
    std::array<std::array<Piece, R>, C> mPieces;
};

