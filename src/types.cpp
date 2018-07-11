#include <cassert>
#include <istream>
#ifndef DGP_NO_ARRAYS
#include <array>
#endif

#include "types.hpp"

// Vec2
#ifndef GDP_STRICT_MEMORY
DGP_FP& Vec2::operator[](size_t index)
{
    assert(index < 2);
    return *(&x + index);
}
const DGP_FP& Vec2::operator[](size_t index) const
{
    assert(index < 2);
    return *(&x + index);
}
#else
DGP_FP& Vec2::operator[](size_t index)
{
    switch (index) {
    case 0: return x;
    case 1: return y;
    default: throw std::out_of_range("Vec2 is a 2-tuple");
    }
}
const DGP_FP& Vec2::operator[](size_t index) const
{
    switch (index) {
    case 0: return x;
    case 1: return y;
    default: throw std::out_of_range("Vec2 is a 2-tuple");
    }
}
#endif

std::istream& operator>>(std::istream& is, Vec2& v)
{
    return (is >> v.x >> v.y);
}

// Vec3
#ifndef GDP_STRICT_MEMORY
DGP_FP& Vec3::operator[](size_t index)
{
    assert(index < 3);
    return *(&x + index);
}
const DGP_FP& Vec3::operator[](size_t index) const
{
    assert(index < 3);
    return *(&x + index);
}
#else
DGP_FP& Vec3::operator[](size_t index)
{
    switch (index) {
    case 0: return x;
    case 1: return y;
    case 2: return z;
    default: throw std::out_of_range("Vertex is a 3-tuple");
    }
}
const DGP_FP& Vec3::operator[](size_t index) const
{
    switch (index) {
    case 0: return x;
    case 1: return y;
    case 2: return z;
    default: throw std::out_of_range("Vertex is a 3-tuple");
    }
}
#endif

std::istream& operator>>(std::istream& is, Vec2& v)
{
    return (is >> v.x >> v.y);
}
