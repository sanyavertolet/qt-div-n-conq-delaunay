#ifndef GEOMETRY_H
#define GEOMETRY_H

#include <QPointF>

/**
 * Geometry namespace contains several functions that can be used for geometry stuff.
 */
namespace Geometry {
    /**
     * @brief isInCircumcircle checks if candidate is in p0-p1-p2 triangle's circumcircle
     * @param p0 first point that defines a triangle
     * @param p1 second point that defines a triangle
     * @param p2 third point that defines a triangle
     * @param candidate point to be checked
     * @return true if candidate is in circumcircle of p0-p1-p2, false otherwise
     */
    bool isInCircumcircle(const QPointF &p0, const QPointF &p1, const QPointF &p2, const QPointF &candidate);

    /**
     * @brief ncos finds strat-central-end angle
     * @param start first angle's vertex
     * @param central central vertex of an angle
     * @param end second angle's vertex
     * @return angle info as qreal
     */
    qreal ncos(QPointF start, const QPointF &central, QPointF end);

    /**
     * @brief det finds the determinant of matrix ( a.x(), b.x() \n a.y() b.y() )
     * @param start first angle's vertex
     * @param central central vertex of an angle
     * @param end second angle's vertex
     * @return determinant of a matrix built with start-central and end-central coordinates
     */
    qreal det(QPointF start, const QPointF &central, QPointF end);

    /**
     * @brief pi 3.14159265359 and so on
     */
    constexpr double pi = M_PI;
}

#endif // GEOMETRY_H
