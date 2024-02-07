#ifndef TRIANGULATOR_H
#define TRIANGULATOR_H

#include "link.h"
#include "node.h"

#include <QList>
#include <QSet>

#include <utility>

/**
 * @brief The Triangulator class does all the maths magic - divide and conquer Delaunay triangulation
 */
class Triangulator {
public:
    using Links = QSet<Link*>;
    using Nodes = QList<Node*>;
    using NodePartition = std::pair<Nodes, Nodes>;

    /**
     * @brief Triangulator default constructor
     */
    Triangulator();

    /**
     * @brief triangulate entry point to triangulation
     * @param nodes set of nodes of a polygon
     * @return links that represent Delaunay triangulation
     */
    Links triangulate(const QSet<Node*> &nodes);

    /**
     * WIP
     *
     * @brief retriangulateNode should use incremental Delaunay triangulation in order to process moved node
     * @param node node that was moved
     * @param nodes list of nodes of a polygon
     * @param links valid Delaunay triangulation
     * @return links that represent Delaunay triangulation
     */
    Links retriangulateNode(Node *node, const Nodes &nodes, const Links &links);

    /**
     * Default destructor
     */
    ~Triangulator();

private:
    /**
     * @brief links links that have been added while triangulation so far
     */
    Links links;

    /**
     * @brief linePrimitive adds a line for two nodes
     * @param nodes list of two nodes to build a line on
     */
    void linePrimitive(const Nodes &nodes);

    /**
     * @brief trianglePrimitive adds a triangle for three nodes
     * @param nodes list of three nodes to build a triangle on
     */
    void trianglePrimitive(const Nodes &nodes);

    /**
     * @brief doTriangulation recursively builds Delaunay triangulation
     * @param nodes list of nodes to build Delaunay triangulation on
     */
    void doTriangulation(const Nodes &nodes);

    /**
     * @brief splitNodes splits nodes into two almost equal groups
     *        (first element of a partition might be bigger in case of odd amount of nodes)
     * @param nodes list of nodes
     * @return pair of two node lists
     */
    NodePartition splitNodes(const Nodes &nodes);

    /**
     * @brief connectVertices connects nodes from left to nodes from right
     * @param left left traingulated part
     * @param right left traingulated part
     */
    void connectVertices(Nodes &left, Nodes &right);

    /**
     * @brief findInitialBaseLink creates initial links that connects two sets of nodes - left and right
     * @param left left triangulated part
     * @param right right triangulated part
     * @return initial links that connects two sets of nodes - left and right
     */
    Link* findInitialBaseLink(Nodes &left, Nodes &right);

    /**
     * @brief makeLink creates a new links that connects two sets of nodes - left and right
     * @param left left triangulated part
     * @param right right triangulated part
     * @param baseLink previously added link
     */
    void makeLink(const Nodes &left, const Nodes &right, const Link *baseLink);

    /**
     * @brief sortCandidates sorts nodes according to the angle with base link
     * @param nodes list of polygon nodes
     * @param newNodes candidate nodes to be in next link
     * @param baseLink previously added link
     * @param isLeftMesh flag that defines if the left set is being processed
     */
    void sortCandidates(const Nodes &nodes, Nodes &newNodes, const Link *baseLink, bool isLeftMesh);

    /**
     * @brief isInCircumcircle checks if candidate is in p0-p1-p2 triangle's circumcircle
     * @param p0 first node that defines a triangle
     * @param p1 second node that defines a triangle
     * @param p2 third node that defines a triangle
     * @param candidate node to be checked
     * @return true if candidate is in circumcircle of p0-p1-p2, false otherwise
     */
    bool isInCircumcircle(const Node *p0, const Node *p1, const Node *p2, const Node *candidate) const;

    /**
     * @brief removeLink removes the link that was build on from and to nodes
     * @param from the first node of a link
     * @param to the second node of a link
     */
    void removeLink(Node *from, Node *to);
};

#endif // TRIANGULATOR_H
