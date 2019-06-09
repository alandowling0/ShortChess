#include "highlightsmodel.h"
#include <QDebug>

HighlightsModel::HighlightsModel()
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

void HighlightsModel::clear()
{
    mDestinations.clear();

    emit destinationsChanged();
}
