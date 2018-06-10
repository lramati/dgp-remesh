#ifndef __VERTEX_HPP__
#define __VERTEX_HPP__

#include <cassert>
#include <istream>
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
    operator const DGP_FP*() const { return &x; }
#endif
    DGP_FP& operator[](size_t index);
    const DGP_FP& operator[](size_t index) const;
    friend std::istream& operator>>(std::istream& is, Vertex& v);
    
    /* Array Interface */
#ifndef DGP_NO_ARRAYS
    Vertex(std::array<DGP_FP, 3> xyz) : Vertex(xyz[0], xyz[1], xyz[2]) {}
#endif
};

class Edge {
public:
    /* Members */
    DGP_VERT_ITR v1, v2;
    
    /* Constructors */
    Edge(DGP_VERT_ITR v1_, DGP_VERT_ITR v2_) : v1(v1_), v2(v1_) {}
    Edge() = default;
    
    /* Accessors */
    DGP_FP getLength() const { return 0; /* TODO: Implement */}
    
    /* Array Interface */
#ifndef DGP_NO_ARRAYS
    Edge(std::array<DGP_VERT_ITR, 2> vs) : Edge(vs[0], vs[1]) {}
#endif
};

#endif /*__VERTEX_HPP__*/
