#include "geometry.h"

#include <cmath>

qreal Geometry::ncos(QPointF start, const QPointF &central, QPointF end) {
    start -= central;
    end -= central;
    auto start_square = QPointF::dotProduct(start, start);
    auto end_square = QPointF::dotProduct(end, end);
    auto distance = std::sqrt(start_square * end_square);
    return -QPointF::dotProduct(start, end) / distance;
}

qreal Geometry::det(QPointF start, const QPointF &central, QPointF end) {
    start -= central, end -= central;
    return (start.x() * end.y() - start.y() * end.x());
}

bool Geometry::isInCircumcircle(const QPointF &p0, const QPointF &p1, const QPointF &p2, const QPointF &candidate) {
    auto dA = QPointF::dotProduct(p0, p0);
    auto dB = QPointF::dotProduct(p1, p1);
    auto dC = QPointF::dotProduct(p2, p2);

    auto aux1 = (dA * (p2.y() - p1.y()) + dB * (p0.y() - p2.y()) + dC * (p1.y() - p0.y()));
    auto aux2 = -(dA * (p2.x() - p1.x()) + dB * (p0.x() - p2.x()) + dC * (p1.x() - p0.x()));
    auto div = (2 * (p0.x() * (p2.y() - p1.y()) + p1.x() * (p0.y() - p2.y()) + p2.x() * (p1.y() - p0.y())));

    if (div == 0) {
        return false;
    }

    QPointF center(aux1 / div, aux2 / div);

    auto double_radius = QPointF::dotProduct(center - p1, center - p1);
    auto distance = QPointF::dotProduct(candidate - center, candidate- center);

    return double_radius > distance;
}
