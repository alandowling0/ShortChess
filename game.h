#pragma once

#include "piece.h"
#include "color.h"
#include "move.h"
#include "board.h"
#include "board.h"
#include <QObject>
#include <vector>


class Game : public QObject
{
    Q_OBJECT

public:
    Game(Board& board);

    void playMove(Move const& move);
    void takebackMove();
    void replayMove();
    void newGame();

    std::vector<Move> getMoves(Square const& origin);
    std::vector<Move> getMovesPlayed() const;
    std::vector<Move> getMovesUndone() const;
    Color sideToMove() const;

private:
    void doMove(Move const& move);
    void undoMove(Move const& move);
    void resetPieces();

    Board& mBoard;
    std::vector<Move> mMoves;
    std::vector<Move> mMovesUndone;
};
