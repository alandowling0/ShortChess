#pragma once

//#include "board.h"
//#include "piece.h"

class Square
{
public:
    Square(int x, int y);

    int x() const;
    int y() const;

//    template <int R, int C>
//    bool isValid(Board<R, C> board)
//    {
//        return mX >= 0 && mX < board.rows() && mY >= 0 && mY < board.columns();
//    }

private:
    int mX;
    int mY;
};


//namespace SquareUtils
//{
//    template <int R, int C>
//    bool isValid(Square const& square, Board<R, C> const& board)
//    {
//        auto x = square.x();
//        auto y = square.y();

//        return x >= 0
//               && x < board.columns()
//               && y >= 0
//               && y < board.rows();
//    }

//    template <int R, int C>
//    bool hasPiece(Square const& square, Board<R, C> const& board)
//    {
//        return board.piece(square) != Piece::ENone;
//    }

//    template <int R, int C>
//    bool isEmpty(Square const& square, Board<R, C> const& board)
//    {
//        return !hasPiece(square, board);
//    }

//    template <int R, int C>
//    bool hasWhitePiece(Board<R, C> const& board, Square const& square)
//    {
//        return PieceUtils::isWhite(board.piece(square));
//    }

//    template <int R, int C>
//    bool hasBlackPiece(Board<R, C> const& board, Square const& square)
//    {
//        return PieceUtils::isBlack(board.piece(square));
//    }
//}

