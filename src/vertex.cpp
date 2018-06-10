#include <cassert>
#include <istream>
#ifndef DGP_NO_ARRAYS
#include <array>
#endif

#include "types.hpp"
#include "vertex.hpp"

#ifndef GDP_STRICT_MEMORY
DGP_FP& Vertex::operator[](size_t index)
{
    assert(index < 3);
    return *(&x + index);
}
const DGP_FP& Vertex::operator[](size_t index) const
{
    assert(index < 3);
    return *(&x + index);
}
#else
DGP_FP& Vertex::operator[](size_t index) {
    switch (index) {
    case 0: return x;
    case 1: return y;
    case 2: return z;
    default: throw std::out_of_range("Vertex is a 3-tuple");
    }
}
const DGP_FP& Vertex::operator[](size_t index) const {
    switch (index) {
    case 0: return x;
    case 1: return y;
    case 2: return z;
    default: throw std::out_of_range("Vertex is a 3-tuple");
    }
}
#endif

std::istream& operator>>(std::istream& is, Vertex& v) {
    return (is >> v.x >> v.y >> v.z);
}
