#ifndef __VERTEX_HPP__
#define __VERTEX_HPP__

#include <cassert>
#include <istream>
#ifndef DGP_NO_ARRAYS
#include <array>
#endif

#include "types.hpp"

Class Vertex;
using vert_edge_data_t = std::pair<Edge*, char>;
using vert_edge_store_t = std::set<vert_edge_data_t, EdgeAngleSort>;
using vert_edge_itr_t = vert_edge_store_t::iterator;

class Edge {
private:
    /* Members */
    Vertex* v1, v2;
    vert_edge_itr_t itr1, itr2;
    bool processing_pending;

    void process_check() const;
public:
    /* Constructors */
    Edge(Vertex* v1_, Vertex* v2_);
    Edge() = default;
    
    /* Accessors */
    Vec2 delta() const;
    DGP_FP getLength() const { return 0; /* TODO: Implement */}
    Vertex& first() { return *v1; }
    const Vertex first() const { return *v1; }
    Vertex& second() { return *v2; }
    const Vertex second() const { return *v2; }
    
    
    /* Manipulators */
    void reposition(char which = -1) const;
    
    /* Array Interface */
#ifndef DGP_NO_ARRAYS
    Edge(std::array<Vertex*, 2> vs) : Edge(vs[0], vs[1]) {}
#endif
};

class EdgeAngleSort {
private:
    Vertex* ref;
    
    
public:
    EdgeAngleSort(Vertex* reference) : ref(reference) {}
    EdgeAngleSort() = delete;
    
    bool operator()(const vert_edge_data_t& lhs,
                    const vert_edge_data_t& rhs) const;
};

class Vertex : public Vec3 {
private:
    /* Members */
    vert_edge_store_t edges;

public:
    /* Constructors */
    Vertex(DGP_FP x_, DGP_FP y_, DGP_FP z_)
            : Vec3(x_, y_, z_), edges(EdgeAngleSort(this)) {}
    Vertex() : Vertex(0.f,0.f,0.f) {}
    
    /* Manipulators */
    vert_edge_itr_t addEdge(Edge* e, char which);
    void removeEdge(const vert_edge_itr_t& itr);
    
    /* Operators */
    
    /* Array Interface */
#ifndef DGP_NO_ARRAYS
    Vertex(std::array<DGP_FP, 3> xyz) : Vertex(xyz[0], xyz[1], xyz[2]) {}
#endif
};


#endif /*__VERTEX_HPP__*/
