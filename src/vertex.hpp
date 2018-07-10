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
    
    /* Constructors */
    Edge(DGP_VERT_ITR v1_, DGP_VERT_ITR v2_) : v1(v1_), v2(v1_) {}
    Edge() = default;
    
    /* Accessors */
    DGP_FP getLength() const { return 0; /* TODO: Implement */}
    Vertex first() { return *v1; }
    Vertex second() { return *v2; }
    
    /* Array Interface */
#ifndef DGP_NO_ARRAYS
    Edge(std::array<DGP_VERT_ITR, 2> vs) : Edge(vs[0], vs[1]) {}
#endif
};

class EdgeSort {
private:
    Vertex* ref;
    
    inline static Vec2 delta(const Edge& e) {
        if (e.first() == *ref) return e.second() - e.first();
        else return e.first() - e.second();
    }
public:
    EdgeSort(Vertex* reference) : ref(reference) {}
    EdgeSort() = delete;
    
    bool operator()(const Edge*& lhs, const Edge*& rhs);
};

class Vertex : public Vec3 {
private:
    /* Members */
    std::set<Edge*, EdgeSort> edges;
public:
    /* Constructors */
    Vertex(DGP_FP x_, DGP_FP y_, DGP_FP z_) : Vec3(x_, y_, z_), edges(EdgeSort(this)) {}
    Vertex() : Vertex(0.f,0.f,0.f) {}
    
    friend std::istream& operator>>(std::istream& is, Vertex& v);
    
    /* Array Interface */
#ifndef DGP_NO_ARRAYS
    Vertex(std::array<DGP_FP, 3> xyz) : Vertex(xyz[0], xyz[1], xyz[2]) {}
#endif
};


#endif /*__VERTEX_HPP__*/
