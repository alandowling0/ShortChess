#include "position.h"


Position::Position(int size) :
    mSideToMove(Color::EWhite),
    mAvailableEnPassant({-1, -1}),
    mWhiteKingMoved(false),
    mWhiteKingsideRookMoved(false),
    mWhiteQueensideRookMoved(false),
    mBlackKingMoved(false),
    mBlackKingsideRookMoved(false),
    mBlackQueensideRookMoved(false)
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

int Position::size() const
{
    return static_cast<int>(mPieces.size());
}

bool Position::isValidSquare(const Square &square) const
{
    auto xValid = (square.x() >= 0) && (square.x() < size());
    auto yValid = (square.y() >= 0) && (square.y() < size());

    return xValid && yValid;
}

void Position::clear()
{
    for(auto & column : mPieces)
    {
        for(auto & piece : column)
        {
            piece = Piece::ENone;
        }
    }
}

Piece Position::piece(const Square &square) const
{
    auto piece = Piece::ENone;

    if(isValidSquare(square))
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

void Position::setPiece(Piece piece, const Square &square)
{
    if(isValidSquare(square))
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

Color Position::sideToMove() const
{
    return mSideToMove;
}

void Position::setSideToMove(Color color)
{
    mSideToMove = color;
}

Square Position::availableEnPassant() const
{
    return mAvailableEnPassant;
}

void Position::setAvailableEnPassant(Square const& availableEnPassant)
{
    mAvailableEnPassant = availableEnPassant;
}

bool Position::whiteKingMoved() const
{
    return mWhiteKingMoved;
}

void Position::setWhiteKingMoved(bool whiteKingMoved)
{
    mWhiteKingMoved = whiteKingMoved;
}

bool Position::whiteKingsideRookMoved() const
{
    return mWhiteKingsideRookMoved;
}

void Position::setWhiteKingsideRookMoved(bool whiteKingsideRookMoved)
{
    mWhiteKingsideRookMoved = whiteKingsideRookMoved;
}

bool Position::whiteQueensideRookMoved() const
{
    return mWhiteQueensideRookMoved;
}

void Position::setWhiteQueensideRookMoved(bool whiteQueensideRookMoved)
{
    mWhiteQueensideRookMoved = whiteQueensideRookMoved;
}

bool Position::blackKingMoved() const
{
    return mBlackKingMoved;
}

void Position::setBlackKingMoved(bool blackKingMoved)
{
    mBlackKingMoved = blackKingMoved;
}

bool Position::blackKingsideRookMoved() const
{
    return mBlackKingsideRookMoved;
}

void Position::setBlackKingsideRookMoved(bool blackKingsideRookMoved)
{
    mBlackKingsideRookMoved = blackKingsideRookMoved;
}

bool Position::blackQueensideRookMoved() const
{
    return mBlackQueensideRookMoved;
}

void Position::setBlackQueensideRookMoved(bool blackQueensideRookMoved)
{
    mBlackQueensideRookMoved = blackQueensideRookMoved;
}


