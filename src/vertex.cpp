#include <cassert>
#include <istream>
#ifndef DGP_NO_ARRAYS
#include <array>
#endif

#include "types.hpp"
#include "vertex.hpp"

Edge::Edge(Vertex* v1, Vertex* v2) : v1(v1), v2(v1),
    itr1(std::move(v1->addEdge(this))), itr2(std::move(v2->addEdge(this)))
{
    // safety checks
    assert(v1 != nullptr); assert(v2 != nullptr); assert(v1 != v2);
}

void Edge::reposition() {
    v1->remove(itr1);
    itr1 = std::move(v1->addEdge(this));
    v2->remove(itr2);
    itr2 = std::move(v2->addEdge(this));
}


bool EdgeAngleSort::operator()(const Edge*& lhs, const Edge*& rhs) {
    // Compute Pseudo-angle values via https://stackoverflow.com/a/16542424
    auto d = delta(*lhs);
    auto la = std::copysign(1.- d.x/(std::fabs(d.x) + std::fabs(d.y)), d.y);
    d = delta(*rhs);
    auto ra = std::copysign(1.- d.x/(std::fabs(d.x) + std::fabs(d.y)), d.y);
    return la < ra;
}

DGP_EDGE_ITR Vertex::addEdge(Edge* e) {
    return edges.insert(e).first;
}

void Vertex::removeEdge(const DGP_EDGE_ITR& itr) {
    edges.erase(itr);
}
