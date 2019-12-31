#pragma once

#include "square.h"
#include "piece.h"

class Move
{
public:
    Move(Square origin, Square destination, Piece piece);
    Move(Square origin, Square destination, Piece piece, Piece captured);
    Move(Square origin, Square destination, Piece piece, Piece captured, bool enPassant);
    Move(Square origin, Square destination, Piece piece, Piece captured, Piece promotionChoice);

    Square origin() const;
    Square destination() const;
    Piece piece() const;
    Piece captured() const;
    bool enPassant() const;
    Piece promotionChoice() const;

private:
    Square mOrigin;
    Square mDestination;
    Piece mPiece;
    Piece mCaptured;
    bool mEnPassant;
    Piece mPromotionChoice;
};

