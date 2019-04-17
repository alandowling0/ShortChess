#pragma once

#include "piecesmodel.h"
#include "highlightsmodel.h"
#include "game.h"

#include <QObject>

class GameController : public QObject
{
    Q_OBJECT
public:
    GameController(Game& piecesModel, HighlightsModel& highlightsModel);

    Q_INVOKABLE void newGame();
    Q_INVOKABLE void showDestinations(int x, int y);
    Q_INVOKABLE void clearDestinations();
    Q_INVOKABLE void doMove(int fromX, int fromY, int toX, int toY);

private:
    Game& mGame;
    HighlightsModel& mHighlightsModel;
};
