#pragma once

#include "piece.h"
#include "color.h"
#include "move.h"
#include "position.h"
#include "piecesmodel.h"
#include "castlingstatus.h"
#include <QObject>
#include <vector>


class Game
{
public:
    Game(PiecesModel& piecesModel);

    void playMove(Move const& move);
    void takebackMove();
    void replayMove();
    void newGame();

    std::vector<Move> getMoves(Square const& origin);
    std::vector<Move> getMovesPlayed() const;
    std::vector<Move> getMovesUndone() const;
    Color getSideToMove() const;

private:
    void doMove(Move const& move);
    void undoMove(Move const& move);
    void resetPieces();

    Position getPosition() const;
    Board getBoard() const;
    CastlingStatus getCastlingStatus() const;
    Square getEnPassantAvailable() const;

    const int mBoardSize = 8;

    PiecesModel& mPiecesModel;
    std::vector<Move> mMoves;
    std::vector<Move> mMovesUndone;
};
