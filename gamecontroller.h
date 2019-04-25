#pragma once

#include "model.h"
#include "game.h"

#include <QObject>

class Controller : public QObject
{
    Q_OBJECT

public:
    Controller(Model& model, Game& game);

    Q_INVOKABLE void newGame();
    Q_INVOKABLE void showDestinations(int x, int y);
    Q_INVOKABLE void clearDestinations();
    Q_INVOKABLE void doMove(int fromX, int fromY, int toX, int toY);

private:
    Model& mModel;
    Game& mGame;
};
