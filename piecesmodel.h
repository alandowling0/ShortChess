#pragma once

#include <QAbstractListModel>
#include <QTimer>
#include <vector>


struct Piece
{
    Piece(QString color, QString type, int x, int y) :
        mColor(color), mType(type), mX(x), mY(y)
    {

    }

    QString mColor;
    QString mType;
    int mX;
    int mY;
};


class PiecesModel : public QAbstractListModel
{
    Q_OBJECT

public:
    enum PieceRole {
        Color = Qt::UserRole + 1,
        Type,
        X,
        Y
    };

    PiecesModel();

    void reset();
    void doMove(int fromX, int fromY, int toX, int toY);

    QHash<int, QByteArray> roleNames() const override;
    QVariant data(const QModelIndex & index, int role) const override;
    int rowCount(const QModelIndex & parent = QModelIndex()) const override;

private:
    std::vector<Piece> mPieces;
};
