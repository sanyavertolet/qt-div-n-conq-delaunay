#ifndef NODE_H
#define NODE_H

#include "nodenotifier.h"

#include "QtCore/qcoreapplication.h"

#include <QPointF>
#include <QGraphicsEllipseItem>
#include <QGraphicsItem>

#include <string>

class Link;

class Node : public QGraphicsItem {
    Q_DECLARE_TR_FUNCTIONS(Node);
public:
    Node(const QPointF &pos, int index = -1);

    int id() const;
    void setText(const QString &text);
    QString text() const;
    void setTextColor(const QColor &color);
    QColor textColor() const;
    void setOutlineColor(const QColor &color);
    QColor outlineColor() const;
    void setBackgroundColor(const QColor &color);
    QColor backgroundColor() const;

    void addLink(Link *link);
    void removeLink(Link *link);
    void removeAllLinks();
    QSet<Link *>& links();

    QRectF boundingRect() const;
    QPainterPath shape() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    bool operator== (const Node &another) const;
    operator std::string() const;
    operator QString() const;

    NodeNotifier notifier;

    ~Node();
protected:
    QVariant itemChange(GraphicsItemChange change, const QVariant &value);

private:
    QRectF outlineRect() const;
    int roundness(double size) const;

    QSet<Link *> nodeLinks;
    QString nodeText;
    QColor nodeTextColor;
    QColor nodeBackgroundColor;
    QColor nodeOutlineColor;
    int nodeIndex;
};

// todo: stop using raw pointers
using NodePtr = std::unique_ptr<Node>;

#endif // NODE_H
