#ifndef __VERTEX_HPP__
#define __VERTEX_HPP__

#include <cassert>
#include <istream>
#ifndef DGP_NO_ARRAYS
#include <array>
#endif

#include "types.hpp"

Class Vertex;
class Edge {
public:
    /* Members */
    Vertex* v1, v2;
    DGP_EDGE_ITR itr1, itr2;
    
    /* Constructors */
    Edge(Vertex* v1_, Vertex* v2_);
    Edge() = default;
    
    /* Accessors */
    DGP_FP getLength() const { return 0; /* TODO: Implement */}
    Vertex first() { return *v1; }
    Vertex second() { return *v2; }
    
    /* Manipulators */
    void reposition();
    
    /* Array Interface */
#ifndef DGP_NO_ARRAYS
    Edge(std::array<Vertex*, 2> vs) : Edge(vs[0], vs[1]) {}
#endif
};

class EdgeAngleSort {
private:
    Vertex* ref;
    
    inline static Vec2 delta(const Edge& e) {
        if (e.first() == *ref) return e.second() - e.first();
        else return e.first() - e.second();
    }
public:
    EdgeAngleSort(Vertex* reference) : ref(reference) {}
    EdgeAngleSort() = delete;
    
    bool operator()(const Edge*& lhs, const Edge*& rhs);
};

class Vertex : public Vec3 {
private:
    /* Members */
    DGP_EDGE_CON edges;
public:
    /* Constructors */
    Vertex(DGP_FP x_, DGP_FP y_, DGP_FP z_) : Vec3(x_, y_, z_), edges(EdgeAngleSort(this)) {}
    Vertex() : Vertex(0.f,0.f,0.f) {}
    
    /* Manipulators */
    DGP_EDGE_ITR addEdge(Edge* e);
    void removeEdge(const DGP_EDGE_ITR& itr);
    
    friend std::istream& operator>>(std::istream& is, Vertex& v);
    
    /* Array Interface */
#ifndef DGP_NO_ARRAYS
    Vertex(std::array<DGP_FP, 3> xyz) : Vertex(xyz[0], xyz[1], xyz[2]) {}
#endif
};


#endif /*__VERTEX_HPP__*/
