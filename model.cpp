#include "model.h"

Model::Model(Game const& game) :
    mGame(game),
    mPiecesModel(std::make_unique<PiecesModel>(game)),
    mHighlightsModel(std::make_unique<HighlightsModel>())
{

}

//QVariant Model::piecesModel() const
//{
//    return QVariant::fromValue(mPiecesModel);
//}

QVariant Model::piecesModel() const
{
    return QVariant::fromValue(mPiecesModel.get());
}

QVariant Model::highlightsModel() const
{
    return QVariant::fromValue(mHighlightsModel.get());
}

void Model::setDestinations(QSet<QPair<int, int>> const& destinations)
{
    if(mHighlightsModel)
    {
        mHighlightsModel->setDestinations(destinations);
    }
    else
    {
        Q_ASSERT(false);
    }
}
