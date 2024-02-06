#include "link.h"

#include <QPen>

#include <sstream>

Link::Link(Node *fromNode, Node *toNode) : from(fromNode), to(toNode) {
    from->addLink(this);
    to->addLink(this);

    setFlags(QGraphicsItem::ItemIsSelectable);
    setZValue(-1);

    setColor(Qt::darkRed);
    trackNodes();
}

Node* Link::fromNode() const {
    return from;
}

Node* Link::toNode() const {
    return to;
}

void Link::setColor(const QColor &color) {
    setPen(QPen(color, 1.0));
}

void Link::trackNodes() {
    setLine(QLineF(from->pos(), to->pos()));
}

bool Link::operator == (const Link &another) const {
    return (from == another.from && to == another.to) || (from == another.to && to == another.from);
}

Link::operator std::string() const {
    std::stringstream s;
    s << std::string(*from) << " -> " << std::string(*to);
    return s.str();
}

Link::operator QString() const {
    return QString::fromStdString(*this);
}

Link::~Link() {
    qDebug() << "Link (" << *this << " was deleted";
    from->removeLink(this);
    to->removeLink(this);
}
