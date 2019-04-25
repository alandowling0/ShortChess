#pragma once

#include <QObject>
#include <memory>
#include "highlightsmodel.h"
#include "piecesmodel.h"
#include "game.h"

class Model : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QVariant piecesModel READ piecesModel CONSTANT)
    Q_PROPERTY(QVariant highlightsModel READ highlightsModel CONSTANT)

public:
    Model(Game const& game);

    QVariant piecesModel() const;
    QVariant highlightsModel() const;

    void setDestinations(QSet<QPair<int, int>> const& destinations);

private:
    Game const& mGame;

    std::unique_ptr<PiecesModel> mPiecesModel;
    std::unique_ptr<HighlightsModel> mHighlightsModel;
};
