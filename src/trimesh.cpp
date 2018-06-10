#include "trimesh.hpp"
#include <fstream>
#include <iostream>
#include <vector>
#include <tuple>

TMesh::TMesh(std::string in_fname) : target_length(0) {
    // command line arg parser enforces existence of the file.
    std::ifstream file(in_fname);
    if (file.fail()) {
        std::cerr << "Failed to open input file" << std::endl;
        exit(1);
    }
    
    /* confirm file is OFF format */
    std::string magic;
    std::getline(file, magic, ' ');
    if (magic != "OFF") {
        std::cerr << "input file is not in required OFF format" << std::endl;
        exit(2);
    }
    
    /* get quantities */
    size_t vs, fs, es;
    file >> vs, fs, es;
    
    /* read in vertices */
    vertices.resize(vs);
    DGP_VERT_ITR iter = std::begin(vertices);
    // Temporary vector for efficient construction of edges
    std::vector<DGP_VERT_ITR> ptrs; ptrs.reserve(vs);
    for (size_t i=0; i < vs; i++) {
        ptrs.push_back(iter);
        file >> *iter++;
    }
    
    /* read in faces */
    std::tuple<unsigned int, unsigned int, unsigned int> face;
}
