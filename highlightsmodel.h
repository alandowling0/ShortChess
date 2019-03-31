#pragma once

#include <QAbstractListModel>
#include <QTimer>
#include <QSet>


class HighlightsModel : public QObject
{
    Q_OBJECT

    Q_PROPERTY(int selected READ selected NOTIFY selectedChanged)
    Q_PROPERTY(QVariantList destinations READ destinations NOTIFY destinationsChanged)

public:
    HighlightsModel();

    int selected() const;
    void setSelected(int selected);

    QVariantList destinations() const;
    void setDestinations(QSet<QPair<int, int>> const& destinations);

    void clear();

signals:
    void selectedChanged();
    void destinationsChanged();

private:
    int mSelected;
    QSet<QPair<int, int>> mDestinations;
};
