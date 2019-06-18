#pragma once

#include <QObject>
#include <QSet>
#include <QPair>
#include <memory>
#include "piecesmodel.h"
#include "game.h"

class Model : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QVariant piecesModel READ piecesModel CONSTANT)
    Q_PROPERTY(QVariantMap selected READ selected NOTIFY selectedChanged)
    Q_PROPERTY(QVariantList highlighted READ highlighted NOTIFY highlightedChanged)
    Q_PROPERTY(bool newGameAvailable READ newGameAvailable NOTIFY newGameAvailableChanged)

public:
    Model();

    Q_INVOKABLE void newGame();
    Q_INVOKABLE void selectSquare(int x, int y);

    QVariant piecesModel() const;
    QVariantMap selected() const;
    QVariantList highlighted() const;
    bool newGameAvailable() const;

signals:
    void selectedChanged();
    void highlightedChanged();
    void newGameAvailableChanged();

private:
    Game mGame;
    std::unique_ptr<PiecesModel> mPiecesModel;
    QPair<int, int> mSelected;
    QSet<QPair<int, int>> mHighlighted;
};
