#ifndef GEOMETRY_H
#define GEOMETRY_H

#include <QPointF>

namespace Geometry {
    bool isInCircumcircle(const QPointF &p0, const QPointF &p1, const QPointF &p2, const QPointF &candidate);

    qreal ncos(QPointF start, const QPointF &central, QPointF end);
    qreal det(QPointF start, const QPointF &central, QPointF end);

    constexpr double pi = M_PI;
}

#endif // GEOMETRY_H
