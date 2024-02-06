#ifndef TRIANGULATOR_H
#define TRIANGULATOR_H

#include "node.h"
#include "link.h"

#include <QSet>
#include <QList>

#include <utility>

class Triangulator {
public:
    using Links = QSet<Link*>;
    using Nodes = QList<Node*>;
    using NodePartition = std::pair<Nodes, Nodes>;

    Triangulator();

    Links triangulate(const QSet<Node*> &nodes);

    Links retriangulateNode(Node *node, const Nodes &nodes, const Links &links);

    ~Triangulator();

private:
    Links links;

    void linePrimitive(const Nodes &nodes);
    void trianglePrimitive(const Nodes &nodes);

    void doTriangulation(const Nodes &nodes);
    NodePartition splitNodes(const Nodes &nodes);
    void connectVertices(Nodes &left, Nodes &right);

    Link* findInitialBaseLink(Nodes &left, Nodes &right);
    void makeLink(const Nodes &left, const Nodes &right, const Link *baseLink);

    void sortCandidates(const Nodes &nodes, Nodes &newNodes, const Link *baseLink, bool isLeftMesh);

    bool isInCircumcircle(const Node *p0, const Node *p1, const Node *p2, const Node *candidate);

    void removeLink(Node *from, Node *to);
};

#endif // TRIANGULATOR_H
