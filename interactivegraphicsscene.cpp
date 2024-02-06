#include "interactivegraphicsscene.h"

#include <QDebug>
#include <QGraphicsEllipseItem>
#include <QGraphicsItem>

InteractiveGraphicsScene::InteractiveGraphicsScene(QObject *parent) : QGraphicsScene(parent) { }

void InteractiveGraphicsScene::mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent) {
    QPointF pos = mouseEvent->scenePos();
    if (mouseEvent->button() == Qt::LeftButton && mouseEvent->modifiers() & Qt::ControlModifier) {
        addNode(pos);
        rebuildLinks();
    } else if (mouseEvent->button() == Qt::LeftButton && mouseEvent->modifiers() & Qt::ShiftModifier) {
        cleanLinks();
        foreach (Node* node, nodes) {
            removeItem(node);
        }
        nodes.clear();
    } else if (mouseEvent->button() == Qt::RightButton && mouseEvent->modifiers() & Qt::ControlModifier) {
        rebuildLinks();
    } else if (mouseEvent->button() == Qt::RightButton) {
        for (auto node : this->selectedItems()) {
            removeNode(dynamic_cast<Node*>(node));
        }
    }

    QGraphicsScene::mousePressEvent(mouseEvent);
}

void InteractiveGraphicsScene::addNode(const QPointF &pos) {
    auto node = new Node(pos, nodeCounter++);
    nodes.insert(node);
    connect(node->notifier, SIGNAL(nodeMoved(int)), this, SLOT(retriangulateNode(int)));
    addItem(node);
    clearSelection();
}

void InteractiveGraphicsScene::removeNode(Node *node) {
    if (node != nullptr) {
        nodes.remove(node);
        removeItem(node);
        delete node;
    }
}

void InteractiveGraphicsScene::rebuildLinks() {
    cleanLinks();
    buildLinks();
}

void InteractiveGraphicsScene::buildLinks() {
    links = triangulator.triangulate(nodes);
    for (const auto &link : links) {
        addItem(link);
    }
}

void InteractiveGraphicsScene::cleanLinks() {
    foreach (Node *node, nodes) {
        node->removeAllLinks();
    }
    foreach (Link *link, links) {
        removeItem(link);
    }
    links.clear();
}

void InteractiveGraphicsScene::retriangulateNode(int nodeId) {
    /*
    auto nodePredicate = [nodeId](Node* node){ return node->id() == nodeId; };
    auto movedNodeIterator = std::find_if(nodes.begin(), nodes.end(), nodePredicate);

    * if (movedNodeIterator != nodes.end()) {
    *     auto movedNode = *movedNodeIterator;
    *     foreach (Link *link, movedNode->links()) {
    *         removeItem(link);
    *         links.remove(link);
    *     }
    *     movedNode->links().clear();
    *
    *     // auto newLinks = triangulator.retriangulateNode(*movedNodeIterator, nodes.values(), links);
    *     auto newLinks = triangulator.triangulate(nodes);
    *     foreach (Link *newLink, newLinks) {
    *         addItem(newLink);
    *         links.insert(newLink);
    *     }
    * }
    */
    rebuildLinks();
}

InteractiveGraphicsScene::~InteractiveGraphicsScene() {
    foreach (Node *node, nodes){
        delete node;
    }
}
