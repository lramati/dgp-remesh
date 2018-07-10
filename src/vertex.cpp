#include <cassert>
#include <istream>
#ifndef DGP_NO_ARRAYS
#include <array>
#endif

#include "types.hpp"
#include "vertex.hpp"

bool EdgeSort::operator()(const Edge*& lhs, const Edge*& rhs) {
    // Compute Pseudo-angle values via https://stackoverflow.com/a/16542424
    auto d = delta(*lhs);
    auto la = std::copysign(1.- d.x/(std::fabs(d.x) + std::fabs(d.y)), d.y);
    d = delta(*rhs);
    auto ra = std::copysign(1.- d.x/(std::fabs(d.x) + std::fabs(d.y)), d.y);
    return la < ra;
}
