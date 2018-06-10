#include "vertex.hpp"
#include "trimesh.hpp"
#include "tclap/CmdLine.h"
#include <string>

#ifndef NDEBUG
#   include <iostream>
#endif

int main (int argc, char const* argv[])
{
    TCLAP::CmdLine cmd("dgp project: Remeshing tool");
    TCLAP::ValueArg<std::string> input_fname("i", "input", "Path to input mesh", true,
                                             "", "off-file");
    TCLAP::ValueArg<std::string> output_fname("o", "output", "Path for output(s)", false,
                                              "./out.off", "off-file");
    TCLAP::ValueArg<std::string> boundary_fname("b", "boundary", "Path to file defining boundary edges as indexed in input file, one per line",
                                                false, "", "boundaries-file");
    TCLAP::ValueArg<size_t> n_iters("n", "iterations", "Number of iterations (default 20)",
                                    false, 20, "integer");
    TCLAP::ValueArg<size_t> intermediates("", "intermediates", "How often to output intermediate meshes (default: don't)",
                                          false, 0, "integer");
    cmd.add(input_fname);
    cmd.add(output_fname);
    cmd.add(boundary_fname);
    cmd.add(n_iters);
    cmd.add(intermediates);
    cmd.parse(argc, argv);
    
    TMesh mesh(input_fname.getValue());
    if (boundary_fname.isSet()) mesh.mark_bounds(boundary_fname.getValue());
    if (n_iters.getValue() == 0) {
        mesh.save(output_fname.getValue());
#ifndef NDEBUG
        std::cout << "WARNING: iterations=0! copying input file to output destination" << std::endl;
#endif
        return 0;
    }
    
    mesh.remesh();
    for (size_t iter=1; iter<n_iters.getValue(); ++iter) {
        if (intermediates.getValue() && (iter%intermediates.getValue()) == 0)
            mesh.save(output_fname.getValue() + "." + std::to_string(iter+1));
        mesh.remesh();
    }
    
    mesh.save(output_fname.getValue());
    
    return 0;
}
