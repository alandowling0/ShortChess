#pragma once

#include "game.h"

#include <QAbstractListModel>
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
    void onPieceAdded(int x, int y, Piece piece);
    void onPieceRemoved(int x, int y);
    void onPiecesReset();

private:
    QString image(Piece piece) const;

    struct PieceInfo
    {
        PieceInfo(QString image, int x, int y) :
            mImage(image), mX(x), mY(y)
        {
        }

        QString mImage;
        int mX;
        int mY;
    };

    enum PieceRole
    {
        Image = Qt::UserRole + 1,
        X,
        Y
    };

    Game const& mGame;
    std::vector<PieceInfo> mPieces;
};
