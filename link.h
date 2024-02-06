#ifndef LINK_H
#define LINK_H

#include "node.h"

#include <QGraphicsLineItem>
#include <QColor>

#include <string>

class Link : public QGraphicsLineItem {
public:
    Link(Node *from_node, Node *to_node);

    Node* fromNode() const;
    Node* toNode() const;
    void setColor(const QColor &color);
    QColor color() const;
    void trackNodes();

    bool operator == (const Link &another) const;

    operator std::string() const;
    operator QString() const;

    ~Link();
private:
    Node *from;
    Node *to;
};

// todo: stop using raw pointers
using LinkPtr = std::unique_ptr<Link>;

#endif // LINK_H
