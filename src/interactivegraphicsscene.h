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
 * @brief The InteractiveGraphicsScene class represents interactive QGraphicsScene that keeps track of all the
 *        graph info (nodes, links) and launches triangulation
 */
class InteractiveGraphicsScene : public QGraphicsScene {
    Q_OBJECT
public:
    /**
     * @brief InteractiveGraphicsScene explicit constructor.
     * @param parent parent QObject element
     */
    explicit InteractiveGraphicsScene(QObject *parent = nullptr);

    /**
     * @brief rebuildLinks removes all links and builds the new ones
     */
    void rebuildLinks();

    /**
     * Almost default destructor
     */
    ~InteractiveGraphicsScene();

protected:
    /**
     * @brief mousePressEvent MousePressed event handler
     * @param event QGraphicsSceneMouseEvent corresponding to occured event
     */
    void mousePressEvent(QGraphicsSceneMouseEvent *event);

private slots:
    /**
     * @brief retriangulateNode slot invoked on node movement (see void NodeNotifier::nodeMoved)
     * @param nodeId id of a node that has been moved
     */
    void retriangulateNode(int nodeId);

private:
    /**
     * @brief nodes QSet of all the nodes that are displayed
     */
    QSet<Node*> nodes;

    /**
     * @brief links QSet of all the links that are displayed
     */
    QSet<Link*> links;

    /**
     * @brief addNode adds a new node to pos position
     * @param pos position of a new node
     */
    void addNode(const QPointF &pos);

    /**
     * @brief removeNode removes requested node
     * @param node node to be deleted
     */
    void removeNode(Node *node);

    /**
     * @brief buildLinks triggers triangulation
     */
    void buildLinks();

    /**
     * @brief cleanLinks removes all the links
     */
    void cleanLinks();

    /**
     * @brief triangulator object that performs all the traingulation - here is all the magic
     */
    Triangulator triangulator;

    /**
     * @brief nodeCounter int counter used to set a valid id to a new child node
     */
    int nodeCounter;
};

#endif // INTERACTIVEGRAPHICSSCENE_H
