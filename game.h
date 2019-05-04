#pragma once

#include "piece.h"
#include "color.h"
#include <QObject>
#include <vector>


struct Move
{
    Move(int originX, int originY, int destinationX, int destinationY) :
        mOriginX(originX),
        mOriginY(originY),
        mDestinationX(destinationX),
        mDestinationY(destinationY)
    {
    }

    int mOriginX;
    int mOriginY;
    int mDestinationX;
    int mDestinationY;
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
    std::vector<Move> getLegalMoves(int originX, int originY) const;

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
