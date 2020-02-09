#include "square.h"

Square::Square(int x, int y) :
    mX(x),
    mY(y)
{

}

int Square::x() const
{
    return mX;
}

int Square::y() const
{
    return mY;
}

bool Square::isValid(const Board &board) const
{
    auto xValid = (mX >= 0) && (mX < board.size());
    auto yValid = (mY >= 0) && (mY < board.size());

    return xValid && yValid;
}
