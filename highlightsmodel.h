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

    void clear();

signals:
    void selectedChanged();
    void destinationsChanged();

private:
    QSet<QPair<int, int>> mDestinations;
};
