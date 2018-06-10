#ifndef __TRIMESH_HPP__
#define __TRIMESH_HPP__

#include "types.hpp"
#include "vertex.hpp"
#include <set>

struct EdgePriCmp { bool operator()(const Edge& lhs, const Edge& rhs) const
        { return lhs.getLength() < rhs.getLength(); } };
class TMesh {
private:
    float target_length;
    DGP_VERT_CON vertices;
    
    std::multiset<Edge, EdgePriCmp> edges;
    
public:
    TMesh(std::string in_fname);

    void remesh(float colinear) {}
    void mark_bounds(std::string bounds_fname) {}
    void save(std::string out_fname) {}
};

#endif /*__TRIMESH_HPP__*/
