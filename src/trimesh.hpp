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
    
    // Multiset is pretty close to min-max heap, which seems like the most
    // useful structure for what's being done
    std::multiset<Edge, EdgePriCmp> edges;
    
    void split_long_edges();
    void join_short_edges();
    void flip_edges();
    void shift_vertices();
    
public:
    TMesh(std::string in_fname);

    void remesh(float colinear) {}
    void mark_bounds(std::string bounds_fname) {}
    void save(std::string out_fname) {}
};

#endif /*__TRIMESH_HPP__*/
