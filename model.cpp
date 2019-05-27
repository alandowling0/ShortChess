#include "model.h"

Model::Model() :
    mPiecesModel(std::make_unique<PiecesModel>(mGame)),
    mHighlightsModel(std::make_unique<HighlightsModel>())
{

}

void Model::newGame()
{
    mGame.newGame();
}

void Model::selectSquare(int x, int y)
{
    auto highlighted = mHighlightsModel->isHighlighted(x, y);

    if(highlighted)
    {
        auto selected = mHighlightsModel->selected();
        mGame.doMove({selected.value("x").toInt(), selected.value("y").toInt(), x, y});
        mHighlightsModel->clear();

        return;
    }

    auto moves = mGame.getLegalMoves(x, y);
    if(moves.empty())
    {
        mHighlightsModel->clear();
        return;
    }

    QSet<QPair<int, int>> destinations;
    for(auto const& m : moves)
    {
        destinations.insert({m.mDestinationX, m.mDestinationY});
    }

    mHighlightsModel->setDestinations(destinations);
    mHighlightsModel->setSelected({x, y});
}

QVariant Model::piecesModel() const
{
    return QVariant::fromValue(mPiecesModel.get());
}

QVariant Model::highlightsModel() const
{
    return QVariant::fromValue(mHighlightsModel.get());
}

