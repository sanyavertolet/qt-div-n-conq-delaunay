#ifndef NODENOTIFIER_H
#define NODENOTIFIER_H

#include <QObject>

class NodeNotifier : public QObject {
    Q_OBJECT
public:
    NodeNotifier();

signals:
    void nodeMoved(int nodeId);

private:
};

#endif // NODENOTIFIER_H
