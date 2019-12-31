#pragma once

#include "board.h"

#include <QAbstractListModel>
#include <vector>


class PiecesModel : public QAbstractListModel
{
    Q_OBJECT

public:
    PiecesModel(Board const& board);

    QHash<int, QByteArray> roleNames() const override;
    QVariant data(const QModelIndex & index, int role) const override;
    int rowCount(const QModelIndex & parent = QModelIndex()) const override;

private slots:
    void onPieceAdded(int index);
    void onPieceRemoved(int index);
    void onPieceMoved(int index);
    void onCleared();

private:
    QString image(Piece piece) const;

    enum PieceRole
    {
        Image = Qt::UserRole + 1,
        X,
        Y
    };

    Board const& mBoard;
};
