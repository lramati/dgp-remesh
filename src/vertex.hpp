#ifndef __VERTEX_HPP__
#define __VERTEX_HPP__

#include <cassert>
#ifndef DGP_NO_ARRAYS
#include <array>
#endif

#include "types.hpp"

class Vertex {
public:
    /* Members */
    DGP_FP x,y,z;
    

    /* Constructors */
    Vertex(DGP_FP x_, DGP_FP y_, DGP_FP z_) : x(x_), y(y_), z(z_) {}
    Vertex() : Vertex(0.f,0.f,0.f) {}
    
    /* Utility Accessors */
#ifndef GDP_STRICT_MEMORY
    operator DGP_FP*() { return &x; }
    DGP_FP& operator[](size_t index) { assert(index < 3); return *(&x + index); }
#else
    DGP_FP& operator[](size_t index) {
        switch (index) {
        case 0: return x; case 1: return y; case 2: return z;
        default: throw std::out_of_range("Vertex is a 3-tuple");
        }
    }
#endif
    friend istream& operator>>(istream& is, Vertex& v);
    
    /* Array Interface */
#ifndef DGP_NO_ARRAYS
    Vertex(std::array<DGP_FP, 3> xyz) : Vertex(xyz[0], xyz[1], xyz[2]) {}
#endif
};

istream& operator>>(istream& is, Vertex& v) {
    return (istream >> v.x >> v.y >> v.z);
}

class Edge {
public:
    /* Members */
    DGP_VERT_ITR v1, v2;
    
    /* Constructors */
    Edge(DGP_VERT_ITR v1_, DGP_VERT_ITR v2_) : v1(v1_), v2(v1_) {}
    Edge() = default;
    
    /* Array Interface */
#ifndef DGP_NO_ARRAYS
    Edge(std::array<DGP_VERT_ITR, 2> vs) : Edge(vs[0], vs[1]) {}
#endif
};

#endif /*__VERTEX_HPP__*/
