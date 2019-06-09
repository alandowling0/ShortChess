#include "piece.h"

bool PieceUtils::isWhite(Piece piece)
{
    return piece == Piece::EWhitePawn ||
            piece == Piece::EWhiteKnight ||
            piece == Piece::EWhiteBishop ||
            piece == Piece::EWhiteRook ||
            piece == Piece::EWhiteQueen ||
            piece == Piece::EWhiteKing;
}

bool PieceUtils::isBlack(Piece piece)
{
    return piece == Piece::EBlackPawn ||
            piece == Piece::EBlackKnight ||
            piece == Piece::EBlackBishop ||
            piece == Piece::EBlackRook ||
            piece == Piece::EBlackQueen ||
            piece == Piece::EBlackKing;
}

