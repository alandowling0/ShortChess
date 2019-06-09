#include "highlightsmodel.h"
#include <QDebug>

HighlightsModel::HighlightsModel() :
    mSelected(-1, -1)
{

}

QVariantList HighlightsModel::destinations() const
{
    QVariantList destinations;

    for(auto const& d : mDestinations)
    {
        QVariantMap destination {{"x", d.first}, {"y", d.second}};
        destinations.push_back(destination);
    }

    return destinations;
}

void HighlightsModel::setDestinations(const QSet<QPair<int, int>> &destinations)
{
    mDestinations = destinations;

    emit destinationsChanged();
}

bool HighlightsModel::isHighlighted(int x, int y) const
{
    return mDestinations.contains({x, y});
}

void HighlightsModel::clear()
{
    mDestinations.clear();
    mSelected.first = -1;
    mSelected.second = -1;

    emit destinationsChanged();
    emit selectedChanged();
}
