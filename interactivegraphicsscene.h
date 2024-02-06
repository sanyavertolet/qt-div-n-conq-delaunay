#ifndef INTERACTIVEGRAPHICSSCENE_H
#define INTERACTIVEGRAPHICSSCENE_H

#include "node.h"
#include "link.h"
#include "triangulator.h"

#include <QGraphicsSceneMouseEvent>
#include <QGraphicsScene>
#include <QPoint>
#include <QSet>

/**
 * @brief The InteractiveGraphicsScene class
 *
 * TODO:
 *  1. Make triangulator work on node position change
 *  2. Keep track of memory - maybe some smart pointers are good here?
 */
class InteractiveGraphicsScene : public QGraphicsScene {
    Q_OBJECT
public:
    explicit InteractiveGraphicsScene(QObject *parent = nullptr);
    void rebuildLinks();

    ~InteractiveGraphicsScene();
protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);

private slots:
    void retriangulateNode(int nodeId);

private:
    QSet<Node*> nodes;
    QSet<Link*> links;

    void addNode(const QPointF &pos);
    void removeNode(Node *node);

    void buildLinks();
    void cleanLinks();

    Triangulator triangulator;

    int nodeCounter;
};

#endif // INTERACTIVEGRAPHICSSCENE_H
