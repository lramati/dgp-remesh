#include <cassert>
#ifndef DGP_NO_ARRAYS
#include <array>
#endif

class Vertex {
public:
    /* Members */
    float x,y,z;

    /* Constructors */
    Vertex(float x_, float y_, float z_) : x(x_), y(y_), z(z_) {}
    Vertex() : Vertex(0.f,0.f,0.f) {}
    
    /* Utility Accessors */
#ifndef GDP_STRICT_MEMORY
    operator float*() { return &x; }
    float& operator[](size_t index) { assert(index < 3); return *(&x + index); }
#else
    float& operator[](size_t index) {
        switch (index) {
        case 0: return x; case 1: return y; case 2: return z;
        default: throw std::out_of_range("Vertex is a 3-tuple");
        }
    }
#endif
    
    /* Array Interface */
#ifndef DGP_NO_ARRAYS
    Vertex(std::array<float, 3> xyz) : Vertex(xyz[0], xyz[1], xyz[2]) {}
#endif
};

class Edge {
public:
    /* Members */
    Vertex *v1, *v2;
    
    /* Constructors */
    Edge(Vertex *v1_, Vertex *v2_) : v1(v1_), v2(v1_) {}
    Edge() : Edge(nullptr, nullptr) {}
    
    /* Array Interface */
#ifndef DGP_NO_ARRAYS
    Edge(std::array<Vertex*, 2> vs) : Edge(vs[0], vs[1]) {}
#endif
};
