#ifndef LINK_H
#define LINK_H

#include "node.h"

#include <QGraphicsLineItem>
#include <QColor>

#include <string>

/**
 * @brief The Link class represents a edge between two nodes as well as its displaying
 */
class Link : public QGraphicsLineItem {
public:
    /**
     * @brief Link the only constructor of Link class
     * @param from_node the first node of a new link
     * @param to_node the second node of a new link
     */
    Link(Node *from_node, Node *to_node);

    /**
     * @brief fromNode from node getter
     * @return the first node of a link
     */
    Node* fromNode() const;

    /**
     * @brief toNode to node getter
     * @return the second node of a link
     */
    Node* toNode() const;

    /**
     * @brief setColor link color setter
     * @param color QColor to be set
     */
    void setColor(const QColor &color);

    /**
     * @brief color link color getter
     * @return color of a link
     */
    QColor color() const;

    /**
     * @brief operator == equals operator, links are equal when they have the same nodes regardless of the order
     * @param another another link
     * @return true if links have the same nodes regardless of the order, false otherwise
     */
    bool operator == (const Link &another) const;

    /**
     * @brief operator std::string stl string casting operator
     */
    operator std::string() const;

    /**
     * @brief operator QString QString casting operator
     */
    operator QString() const;

    /**
     * Simple destructor
     */
    ~Link();

private:
    /**
     * @brief from the first node of a link
     */
    Node *from;

    /**
     * @brief to the second node of a link
     */
    Node *to;
};

#endif // LINK_H
