#pragma once

#include <QObject>
#include <QSet>
#include <QPair>
#include <memory>
#include "piecesmodel.h"
#include "game.h"
#include "board.h"

class Model : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QVariant piecesModel READ piecesModel CONSTANT)
    Q_PROPERTY(QVariantMap selected READ selected NOTIFY selectedChanged)
    Q_PROPERTY(QVariantList highlighted READ highlighted NOTIFY highlightedChanged)
    Q_PROPERTY(bool newGameAvailable READ newGameAvailable NOTIFY gameStateChanged)
    Q_PROPERTY(bool undoMoveAvailable READ undoMoveAvailable NOTIFY gameStateChanged)
    Q_PROPERTY(bool redoMoveAvailable READ redoMoveAvailable NOTIFY gameStateChanged)

public:
    Model();

    Q_INVOKABLE void newGame();
    Q_INVOKABLE void undoMove();
    Q_INVOKABLE void redoMove();
    Q_INVOKABLE void selectSquare(int x, int y);

    QVariant piecesModel() const;
    QVariantMap selected() const;
    QVariantList highlighted() const;
    bool newGameAvailable() const;
    bool undoMoveAvailable() const;
    bool redoMoveAvailable() const;

signals:
    void selectedChanged();
    void highlightedChanged();
    void gameStateChanged();

private:
    Board mBoard;
    Game mGame;
    std::unique_ptr<PiecesModel> mPiecesModel;
    QPair<int, int> mSelected;
    QSet<QPair<int, int>> mHighlighted;
};
