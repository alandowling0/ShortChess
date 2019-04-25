#include "gamecontroller.h"
#include <QSet>
#include <QPair>

Controller::Controller(Model& model, Game& game) :
    mModel(model),
    mGame(game)
{
}

void Controller::newGame()
{
    mGame.newGame();
    //mHighlightsModel.clear();
}

void Controller::showDestinations(int x, int y)
{
    QSet<QPair<int, int>> destinations;

    for(auto const& m : mGame.getLegalMoves(x, y))
    {
        destinations.insert({m.mDestinationX, m.mDestinationY});
    }

    mModel.setDestinations(destinations);
}

void Controller::clearDestinations()
{
    //mHighlightsModel.clear();
}

void Controller::doMove(int fromX, int fromY, int toX, int toY)
{
    mGame.playMove(Move(fromX, fromY, toX, toY));
}

