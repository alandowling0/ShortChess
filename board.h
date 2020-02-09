#pragma once

#include "piece.h"
#include <vector>

class Square;

class Board
{
public:
    Board(int size);

    int size() const;
    Piece piece(Square const& square) const;
    void setPiece(Square const& square, Piece piece);

private:
    std::vector<std::vector<Piece>> mPieces;
};

