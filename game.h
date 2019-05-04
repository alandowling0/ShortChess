#pragma once

#include "piece.h"
#include "color.h"
#include <QObject>
#include <vector>


struct Move
{
    Move(size_t originX, size_t originY, size_t destinationX, size_t destinationY) :
        mOriginX(originX),
        mOriginY(originY),
        mDestinationX(destinationX),
        mDestinationY(destinationY)
    {
    }

    size_t mOriginX;
    size_t mOriginY;
    size_t mDestinationX;
    size_t mDestinationY;
};

class Game : public QObject
{
    Q_OBJECT

public:
    Game();

    void playMove(Move const& aMove);
    void undoMove();
    void redoMove();
    void newGame();

    std::vector<std::vector<Piece>> getBoard() const;
    std::vector<Move> getMovesPlayed() const;
    std::vector<Move> getLegalMoves(size_t x, size_t y) const;

signals:
    void pieceMoved(int originX, int originY, int destinationX, int destinationY);
    void pieceAdded();
    void pieceRemoved(int x, int y);
    void piecesReset();

private:
    void resetPieces();
    Color sideToMove() const;

    std::vector<std::vector<Piece>> mBoard;
    std::vector<Move> mMoves;
};
