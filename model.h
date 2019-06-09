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
    Q_PROPERTY(QVariantMap selectedSquare READ selectedSquare NOTIFY selectedSquareChanged)

public:
    Model();

    Q_INVOKABLE void newGame();
    Q_INVOKABLE void selectSquare(int x, int y);

    QVariant piecesModel() const;
    QVariant highlightsModel() const;
    QVariantMap selectedSquare() const;

signals:
    void selectedSquareChanged();

private:
    Game mGame;
    std::unique_ptr<PiecesModel> mPiecesModel;
    std::unique_ptr<HighlightsModel> mHighlightsModel;
    int mSelectedX;
    int mSelectedY;
};
