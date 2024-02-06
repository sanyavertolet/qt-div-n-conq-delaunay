#include "triangulator.h"

#include <cmath>
#include <geometry.h>

Triangulator::Triangulator() { }

void Triangulator::linePrimitive(const Triangulator::Nodes &nodes) {
    auto linePrimitive = new Link(nodes[0], nodes[1]);
    qDebug() << "Adding line primitive" << *linePrimitive;
    links.insert(linePrimitive);
}

void Triangulator::trianglePrimitive(const Triangulator::Nodes &nodes) {
    for (int i = 0; i < 3; ++i) {
        auto trianglePrimitive = new Link(nodes[i], nodes[(i + 1) % 3]);
        qDebug() << "Adding triangle primitive" << *trianglePrimitive;
        links.insert(trianglePrimitive);
    }
}

Triangulator::Links Triangulator::triangulate(const QSet<Node*> &nodes) {
    links.clear();
    if (nodes.size() < 2) {
        return links;
    }
    auto nodeList = nodes.values();
    std::sort(nodeList.begin(), nodeList.end(), [](Node *a, Node *b) { return a->x() < b->x(); });
    doTriangulation(nodeList);
    return links;
}

void Triangulator::doTriangulation(const Triangulator::Nodes &nodes) {
    if (nodes.length() == 2) {
        return linePrimitive(nodes);
    } else if (nodes.length() == 3) {
        return trianglePrimitive(nodes);
    }
    auto [left, right] = splitNodes(nodes);

    doTriangulation(left);
    doTriangulation(right);

    connectVertices(left, right);
}

Triangulator::NodePartition Triangulator::splitNodes(const Triangulator::Nodes &nodes) {
    auto size = nodes.size();

    QList<Node*> left(nodes.mid(0, std::ceil(size / 2.0)));
    QList<Node*> right(nodes.mid(std::ceil(size / 2.0), size));
    return { left, right };
}

void Triangulator::connectVertices(Triangulator::Nodes &left, Triangulator::Nodes &right) {
    Link* baseLink = findInitialBaseLink(left, right);
    links.insert(baseLink);

    qDebug() << "Base link: " << *baseLink;

    makeLink(left, right, baseLink);
}

Link* Triangulator::findInitialBaseLink(Nodes &left, Nodes &right) {
    auto predicate = [](Node *lhs, Node *rhs) { return lhs->y() < rhs->y(); };
    std::sort(left.begin(), left.end(), predicate);
    std::sort(right.begin(), right.end(), predicate);

    auto leftMin = left.front();
    auto rightMin = right.front();

    for (int i = 1; i < right.size() ; ++i){
        if (Geometry::det(rightMin->pos(), leftMin->pos(), right[i]->pos()) < 0) {
            rightMin = right[i];
        }
        if (right[i]->y() > rightMin->y() && right[i]->y() > leftMin->y()) {
            break;
        }
    }
    for (int i = 1; i < left.size(); ++i) {
        if (Geometry::det(leftMin->pos(), rightMin->pos(), left[i]->pos()) > 0) {
            leftMin = left[i];
        }
        if (left[i]->y() > rightMin->y() && left[i]->y() > leftMin->y()) {
            break;
        }
    }
    return new Link(leftMin, rightMin);
}

void Triangulator::makeLink(const Nodes &left, const Nodes &right, const Link *baseLink) {
    Nodes leftCandidates, rightCandidates;
    sortCandidates(left, leftCandidates, baseLink , true);
    sortCandidates(right, rightCandidates, baseLink , false);

    Node* leftCandidate = nullptr;
    for (int i = 0; i < leftCandidates.size(); ++i){
        if (i + 1 == leftCandidates.size()) {
            leftCandidate = leftCandidates[i];
            break;
        }
        bool del=false;
        for (int j = i + 1; j < leftCandidates.size(); ++j) {
            if (isInCircumcircle(baseLink->fromNode(), baseLink->toNode(), leftCandidates[i], leftCandidates[j])) {
                removeLink(baseLink->fromNode(), leftCandidates[i]);
                del = true;
                break;
            }
        }

        if (!del){
            leftCandidate = leftCandidates[i];
            break;
        }
    }

    Node *rightCandidate = nullptr;
    for (int i = 0; i < rightCandidates.size(); ++i) {
        if (i + 1 == rightCandidates.size()){
            rightCandidate = rightCandidates[i];
            break;
        }

        bool del = false;
        for (int j = i + 1; j < rightCandidates.size(); ++j) {
            if (isInCircumcircle(baseLink->fromNode(), baseLink->toNode(), rightCandidates[i], rightCandidates[j])){
                removeLink(baseLink->toNode(), rightCandidates[i]);
                del = true;
                break;
            }
        }

        if (!del) {
            rightCandidate = rightCandidates[i];
            break;
        }
    }

    if (leftCandidate) {
        qDebug() << "Left candidate is selected" << *leftCandidate;
    }
    if (rightCandidate) {
        qDebug() << "Right candidate is selected" << *rightCandidate;
    }

    bool isRightContainLeft = false;
    bool isLeftContainRight = false;
    Link *newLink = nullptr;
    if (leftCandidate != nullptr && rightCandidate != nullptr) {
        isRightContainLeft = isInCircumcircle(baseLink->fromNode(), baseLink->toNode(), rightCandidate, leftCandidate);
        isLeftContainRight = isInCircumcircle(baseLink->fromNode(), baseLink->toNode(), leftCandidate, rightCandidate);
        assert(isRightContainLeft || isLeftContainRight);
        if (isRightContainLeft){
            newLink = new Link(leftCandidate, baseLink->toNode());
        } else {
            newLink = new Link(baseLink->fromNode(), rightCandidate);
        }
    } else if (leftCandidate != nullptr) {
        newLink = new Link(leftCandidate, baseLink->toNode());
    } else if (rightCandidate != nullptr) {
        newLink = new Link(baseLink->fromNode(), rightCandidate);
    } else {
        return;
    }

    qDebug() << "Adding link" << *newLink;
    links.insert(newLink);
    makeLink(left, right, newLink);
}

void Triangulator::sortCandidates(const Nodes &nodes, Nodes &newNodes, const Link *baseLink, bool isLeftMesh) {
    auto left = baseLink->fromNode();
    auto right = baseLink->toNode();

    std::vector<std::pair<double, Node*>> data;
    if (isLeftMesh) {
        for (int i = 0; i < nodes.size(); ++i) {
            auto p = nodes[i];
            if (Geometry::det(right->pos(), left->pos(), p->pos()) > 0) {
                auto angle = Geometry::ncos(right->pos(), left->pos(), p->pos());
                data.push_back({ angle, p });
            }
        }
    } else {
        for (int i = 0; i < nodes.size(); ++i) {
            auto p = nodes[i];
            if (Geometry::det(p->pos(), right->pos(), left->pos()) > 0) {
                auto angle = Geometry::ncos(left->pos(), right->pos(), p->pos());
                data.push_back({ angle, p });
            }
        }
    }
    std::sort(data.begin(), data.end());

    for(auto [angle, node] : data) {
        newNodes.push_back(node);
    }
}

bool Triangulator::isInCircumcircle(const Node *p0, const Node *p1, const Node *p2, const Node *candidate) const {
    return Geometry::isInCircumcircle(p0->pos(), p1->pos(), p2->pos(), candidate->pos());
}

void Triangulator::removeLink(Node *from, Node *to) {
    auto predicate = [&from, &to](Link *link) {
        if (link && *link == Link(from, to)) {
            link->fromNode()->links().remove(link);
            link->toNode()->links().remove(link);
            delete link;
            return true;
        }
        return false;
    };
    auto deleted = links.removeIf(predicate);
    qDebug() << "Deleted " << deleted << " links" << Link(from, to);
}

Triangulator::Links Triangulator::retriangulateNode(Node *node, const Nodes &nodes, const Links &links) {
    // todo: delete all links that have `node` in either `Link::from` or `Link::to.
    // todo: insert a `node` into triangulated `links`
    return Links();
}


Triangulator::~Triangulator() {}
