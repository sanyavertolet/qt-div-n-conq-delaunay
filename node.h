#ifndef NODE_H
#define NODE_H

#include "nodenotifier.h"

#include "QtCore/qcoreapplication.h"

#include <QPointF>
#include <QGraphicsEllipseItem>
#include <QGraphicsItem>

#include <string>

class Link;

/**
 * @brief The Node class represents a polygon vertex as well as its displaying
 */
class Node : public QGraphicsItem {
    Q_DECLARE_TR_FUNCTIONS(Node);
public:
    /**
     * @brief Node the only constructor of Node class
     * @param pos desired position of Node as QPointF
     * @param index node index, -1 by default
     */
    Node(const QPointF &pos, int index = -1);

    /**
     * @brief id node id getter
     * @return nodeIndex
     */
    int id() const;

    /**
     * @brief text node text getter
     * @return nodeText as QString
     */
    QString text() const;

    /**
     * @brief textColor node text color getter
     * @return nodeTextColor as QColor
     */
    QColor textColor() const;

    /**
     * @brief outlineColor outline color getter
     * @return nodeOutlineColor as QColor
     */
    QColor outlineColor() const;

    /**
     * @brief backgroundColor background color getter
     * @return nodeBackgroundColor as QColor
     */
    QColor backgroundColor() const;

    /**
     * @brief setText node text setter
     * @param text QString text to be set
     */
    void setText(const QString &text);


    /**
     * @brief setTextColor text color setter
     * @param color desired node color as QColor
     */
    void setTextColor(const QColor &color);

    /**
     * @brief setOutlineColor outline color setter
     * @param color desired node color as QColor
     */
    void setOutlineColor(const QColor &color);

    /**
     * @brief setBackgroundColor background color setter
     * @param color desired node background color as QColor
     */
    void setBackgroundColor(const QColor &color);

    /**
     * @brief addLink adds a new link to node
     * @param link link to be added to nodeLinks
     */
    void addLink(Link *link);

    /**
     * @brief removeLink removes link from node links, does nothing if link is not present
     * @param link link to be deleted from nodeLinks
     */
    void removeLink(Link *link);

    /**
     * @brief removeAllLinks removes all links from node
     */
    void removeAllLinks();

    /**
     * @brief links node links getter - notice that it returns a reference to links
     * @return nodeLinks as a reference to QSet object
     */
    QSet<Link *>& links();

    /**
     * @brief boundingRect calculates the bounding rectangle of a node
     * @return QRectF that represents the bounding rectangle of a node
     */
    QRectF boundingRect() const;

    /**
     * @brief shape calculates the shape of a node
     * @return QPainterPath containing a bounding rectangle of a node
     */
    QPainterPath shape() const;

    /**
     * @brief paint defines how the node should be displayed on QGraphicsView
     * @param painter QPainter object
     * @param option display options
     * @param widget QWidget object
     */
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    /**
     * @brief operator ==
     * @param another another node to compare with
     * @return true if nodes have the same id (nodeIndex), false otherwise
     */
    bool operator== (const Node &another) const;

    /**
     * @brief operator QString c++ string casting operator
     */
    operator std::string() const;

    /**
     * @brief operator QString QString casting operator
     */
    operator QString() const;

    /**
     * @brief notifier QObject that is used by node to send signals to InteractiveGraphicsScene
     */
    NodeNotifier notifier;

    /**
     * Almost default destructor
     */
    ~Node();
protected:
    /**
     * @brief itemChange callback invoked when node position changed
     * @param change GraphicsItemChange object
     * @param value QVariant object
     * @return QVariant object
     */
    QVariant itemChange(GraphicsItemChange change, const QVariant &value);

private:
    /**
     * @brief outlineRect calculates outline rectangle of a node according to the displayed node text
     * @return outline rectangle of a node
     */
    QRectF outlineRect() const;

    /**
     * @brief roundness calculates the node roundness
     * @param size
     * @return roundness of a node
     */
    int roundness(double size) const;

    /**
     * @brief nodeLinks set of links that connect the node to the other nodes
     */
    QSet<Link *> nodeLinks;

    /**
     * @brief nodeText text that is displayed inside a node
     */
    QString nodeText;

    /**
     * @brief nodeTextColor node text color
     */
    QColor nodeTextColor;

    /**
     * @brief nodeBackgroundColor node background color
     */
    QColor nodeBackgroundColor;

    /**
     * @brief nodeOutlineColor node outline color
     */
    QColor nodeOutlineColor;

    /**
     * @brief nodeIndex id of a node
     */
    int nodeIndex;
};

#endif // NODE_H
