#pragma once

#include <QAbstractListModel>
#include <QTimer>
#include <QSet>


class HighlightsModel : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QVariantList destinations READ destinations NOTIFY destinationsChanged)

public:
    HighlightsModel();

    QVariantList destinations() const;
    void setDestinations(QSet<QPair<int, int>> const& destinations);

    bool isHighlighted(int x, int y) const;


    void clear();

signals:
    void selectedChanged();
    void destinationsChanged();

private:
    QPair<int, int> mSelected;
    QSet<QPair<int, int>> mDestinations;
};
