#pragma once

#include "piece.h"
#include "color.h"
#include "move.h"
#include "board.h"
#include <QObject>
#include <vector>


class Game : public QObject
{
    Q_OBJECT

public:
    Game();

    void playMove(Move const& move);
    void undoMove();
    void redoMove();
    void newGame();

    Board<8, 8> getBoard() const;
    std::vector<Move> getMovesPlayed() const;
    std::vector<Move> getMovesUndone() const;
    std::vector<Move> getLegalMoves(int x, int y) const;
    Color sideToMove() const;

signals:
    void pieceMoved(int originX, int originY, int destinationX, int destinationY);
    void pieceAdded(int x, int y, Piece piece);
    void pieceRemoved(int x, int y);
    void piecesReset();

private:
    void doMove(Move const& move);
    void resetPieces();

    Board<8, 8> mBoard;
    std::vector<Move> mMoves;
    std::vector<Move> mMovesUndone;
};
