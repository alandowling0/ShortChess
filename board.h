#pragma once

#include <vector>
#include "piece.h"

class Board
{
public:
    Board(int size);

    int size() const;
    Piece piece(int x, int y) const;
    void setPiece(int x, int y, Piece piece);

private:
    size_t mSize;
    std::vector<std::vector<Piece>> mPieces;
};
