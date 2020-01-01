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
    Q_PROPERTY(bool newGameAvailable READ newGameAvailable NOTIFY gameStateChanged)
    Q_PROPERTY(bool takebackMoveAvailable READ takebackMoveAvailable NOTIFY gameStateChanged)
    Q_PROPERTY(bool replayMoveAvailable READ replayMoveAvailable NOTIFY gameStateChanged)

public:
    Model();

    Q_INVOKABLE void clickSquare(int x, int y);
    Q_INVOKABLE void takebackMove();
    Q_INVOKABLE void replayMove();
    Q_INVOKABLE void newGame();

    QVariant piecesModel() const;
    QVariantMap selected() const;
    QVariantList highlighted() const;
    bool newGameAvailable() const;
    bool takebackMoveAvailable() const;
    bool replayMoveAvailable() const;

signals:
    void selectedChanged();
    void highlightedChanged();
    void gameStateChanged();

private:
    std::unique_ptr<PiecesModel> mPiecesModel;
    Game mGame;

    Square mSelected;
    QSet<Square> mHighlighted;
};
