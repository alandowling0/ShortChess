#pragma once

#include <array>
#include <QtGlobal>
#include "piece.h"
#include "square.h"

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

    Piece piece(Square square) const
    {
        if(isValid(square))
        {
            return mPieces[square.x()][square.y()];
        }
        else
        {
            Q_ASSERT(false);
            return Piece::ENone;
        }
    }

    void setPiece(Square square, Piece piece)
    {
        mPieces[square.x()][square.y()] = piece;
    }

    bool isValid(Square const& square) const
    {
        auto xValid = square.x() >= 0 && square.x() < C;
        auto yValid = square.y() >= 0 && square.y() < R;

        return xValid && yValid;
    }

private:
    std::array<std::array<Piece, R>, C> mPieces;
};



