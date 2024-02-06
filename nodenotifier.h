#ifndef NODENOTIFIER_H
#define NODENOTIFIER_H

#include <QObject>

/**
 * @brief The NodeNotifier class that is capable of sending signals to InteractiveGraphicsScene
 */
class NodeNotifier : public QObject {
    Q_OBJECT
public:
    /**
     * @brief NodeNotifier default constructor
     */
    NodeNotifier();

signals:
    /**
     * @brief nodeMoved signal that is being emitted by node meaning that it was moved
     * @param nodeId id of a node that was moved
     */
    void nodeMoved(int nodeId);
};

#endif // NODENOTIFIER_H
