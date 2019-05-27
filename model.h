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
    Model();

    Q_INVOKABLE void newGame();
    Q_INVOKABLE void selectSquare(int x, int y);

    QVariant piecesModel() const;
    QVariant highlightsModel() const;

private:
    Game mGame;
    std::unique_ptr<PiecesModel> mPiecesModel;
    std::unique_ptr<HighlightsModel> mHighlightsModel;
};
