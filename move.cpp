#include "move.h"


Move::Move(Square origin, Square destination, Piece piece) :
    Move(origin, destination, piece, Piece::ENone, false)
{
}

Move::Move(Square origin, Square destination, Piece piece, Piece captured) :
    Move(origin, destination, piece, captured, false)
{
}

Move::Move(Square origin, Square destination, Piece piece, Piece captured, bool enPassant) :
    mOrigin(origin),
    mDestination(destination),
    mPiece(piece),
    mCaptured(captured),
    mEnPassant(enPassant),
    mPromotionChoice(Piece::ENone)
{
}

Move::Move(Square origin, Square destination, Piece piece, Piece captured, Piece promotionChoice) :
    mOrigin(origin),
    mDestination(destination),
    mPiece(piece),
    mCaptured(captured),
    mEnPassant(false),
    mPromotionChoice(promotionChoice)
{
}

Square Move::origin() const
{
    return mOrigin;
}

Square Move::destination() const
{
    return mDestination;
}

Piece Move::piece() const
{
    return mPiece;
}

Piece Move::captured() const
{
    return mCaptured;
}

bool Move::enPassant() const
{
    return mEnPassant;
}

Piece Move::promotionChoice() const
{
    return mPromotionChoice;
}
