#include "node.h"

#include "link.h"

#include <QApplication>
#include <QFontMetricsF>
#include <QPainter>
#include <QPainterPath>
#include <QStyle>
#include <QStyleOptionGraphicsItem>

#include <sstream>

Node::Node(const QPointF &pos, int index) :
    notifier(NodeNotifier()),
    nodeTextColor(Qt::darkGreen),
    nodeBackgroundColor(Qt::white),
    nodeOutlineColor(Qt::darkBlue),
    nodeIndex(index) {
    setFlags(ItemIsMovable | ItemIsSelectable | ItemSendsGeometryChanges);
    setPos(pos);
    setText(QString::number(index));
    qDebug() << "Point added: " << *this;
}

int Node::id() const {
    return nodeIndex;
}

void Node::setText(const QString &text) {
    prepareGeometryChange();
    nodeText = text;
    update();
}

void Node::setTextColor(const QColor &color) {
    nodeTextColor = color;
    update();
}

void Node::addLink(Link *link) {
    nodeLinks.insert(link);
}

void Node::removeLink(Link *link) {
    nodeLinks.remove(link);
}

void Node::removeAllLinks() {
    nodeLinks.clear();
}

QSet<Link *>& Node::links() {
    return nodeLinks;
}

QRectF Node::outlineRect() const {
    const int padding = 8;
    QFontMetricsF metrics = QFontMetricsF(qApp->font());
    QRectF rect = metrics.boundingRect(nodeText);
    rect.adjust(-padding, -padding, +padding, +padding);
    rect.translate(-rect.center());
    return rect;
}

QRectF Node::boundingRect() const {
    const int margin = 1;
    return outlineRect().adjusted(-margin, -margin, +margin, +margin);
}

QPainterPath Node::shape() const {
    QRectF rect = outlineRect();

    QPainterPath path;
    path.addRoundedRect(rect, roundness(rect.width()), roundness(rect.height()));
    return path;
}

void Node::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget * /* widget */) {
    QPen pen(nodeOutlineColor);
    if (option->state & QStyle::State_Selected) {
        pen.setStyle(Qt::DotLine);
        pen.setWidth(2);
    }
    painter->setPen(pen);
    painter->setBrush(nodeBackgroundColor);

    QRectF rect = outlineRect();
    painter->drawRoundedRect(rect, roundness(rect.width()), roundness(rect.height()));

    painter->setPen(nodeTextColor);
    painter->drawText(rect, Qt::AlignCenter, nodeText);
}

QVariant Node::itemChange(GraphicsItemChange change, const QVariant &value) {
    if (change == ItemPositionHasChanged) {
        emit notifier.nodeMoved(nodeIndex);
    }
    return QGraphicsItem::itemChange(change, value);
}

int Node::roundness(double size) const {
    constexpr int diameter = 12;
    return 100 * diameter / int(size);
}

bool Node::operator== (const Node &another) const {
    return nodeIndex != -1 && nodeIndex == another.nodeIndex;
}

Node::operator std::string() const {
    std::stringstream s;
    s << nodeIndex << " (" << x() << ", " << y() << ")";
    return s.str();
}

Node::operator QString() const {
    return QString::fromStdString(*this);
}

Node::~Node() {
    qDebug() << "Deleted node " << *this;
}
