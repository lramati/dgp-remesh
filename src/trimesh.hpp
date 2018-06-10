#ifndef __TRIMESH_HPP__
#define __TRIMESH_HPP__

#include "vertex.hpp"
#include <string>


class TMesh {
private:
    
public:
    TMesh(std::string in_fname) {}

    void remesh(float colinear) {}
    void mark_bounds(std::string bounds_fname) {}
    void save(std::string out_fname) {}
};

#endif /*__TRIMESH_HPP__*/
