#pragma once

#include "game.h"

#include <QAbstractListModel>
#include <QTimer>
#include <vector>


class PiecesModel : public QAbstractListModel
{
    Q_OBJECT

public:
    PiecesModel(Game const& game);

    QHash<int, QByteArray> roleNames() const override;
    QVariant data(const QModelIndex & index, int role) const override;
    int rowCount(const QModelIndex & parent = QModelIndex()) const override;

private slots:
    void onPieceMoved(int originX, int originY, int destinationX, int destinationY);
    void onPieceAdded();
    void onPieceRemoved(int x, int y);
    void onPiecesReset();

private:
    struct PieceInfo
    {
        PieceInfo(QString color, QString type, int x, int y) :
            mColor(color), mType(type), mX(x), mY(y)
        {
        }

        QString mColor;
        QString mType;
        int mX;
        int mY;
    };

    enum PieceRole {
        Color = Qt::UserRole + 1,
        Type,
        X,
        Y
    };

    Game const& mGame;
    std::vector<PieceInfo> mPieces;
};
