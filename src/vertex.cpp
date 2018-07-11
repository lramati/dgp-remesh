#include <cassert>
#include <istream>
#ifndef DGP_NO_ARRAYS
#include <array>
#endif

#include "types.hpp"
#include "vertex.hpp"

Edge::Edge(Vertex* v1, Vertex* v2) : v1(v1), v2(v1), processing_pending(false),
    itr1(std::move(v1->addEdge(this, 0))), itr2(std::move(v2->addEdge(this, 1)))
{
    // safety checks
    assert(v1 != nullptr); assert(v2 != nullptr); assert(v1 != v2);
    
    // global registration
    process_check();
}

// TODO: Not sold on this. Should I keep large/small queues separate?
// requires more bookkeeping, but would allow use of std::priority_queue
void Edge::process_check() const
{
    if (processing_pending) return;
    auto len = length();
    if (len > Globals::max_length() || len < Globals::min_length()) {
        Globals::edge_queue.insert(this);
        processing_pending = true;
    }
}

Vec2 Edge::delta() const
{
    return *v1 - *v2;
}

void Edge::reposition(char which) const
{
    // This method allows -1 to mean both
    if (which != 1) {
        v1->remove(itr1);
        itr1 = std::move(v1->addEdge(this, 0));
    }
    if (which != 0) {
        v2->remove(itr2);
        itr2 = std::move(v2->addEdge(this, 1));
    }
    
    process_check();
}


bool EdgeAngleSort::operator()(const vert_edge_data_t& lhs,
                               const vert_edge_data_t& rhs) const
{
    // Compute Pseudo-angle values via https://stackoverflow.com/a/16542424
    auto d = (lhs.second == 0)? delta(*(lhs.first)) : -delta(*(lhs.first));
    auto la = std::copysign(1.- d.x/(std::fabs(d.x) + std::fabs(d.y)), d.y);
    auto d = (rhs.second == 0)? delta(*(rhs.first)) : -delta(*(rhs.first));
    auto ra = std::copysign(1.- d.x/(std::fabs(d.x) + std::fabs(d.y)), d.y);
    return la < ra;
}

vert_edge_itr_t Vertex::addEdge(Edge* e, char which)
{
    return edges.emplace(e, which).first;
}

void Vertex::removeEdge(const vert_edge_itr_t& itr)
{
    edges.erase(itr);
}
