#include "vertex.hpp"
#include "trimesh.hpp"
#include "tclap/CmdLine.h"
#include <string>
#include <vector>

#ifndef NDEBUG
#   include <iostream>
#endif

#ifndef DGP_FORCE_COLINEAR
#define DEFAULT_COLINEARITY 0.05
#define str(s) xstr(s)
#define xstr(s) #s
class NonNegConstraint : public TCLAP::Constraint<DGP_FP> {
public:
    NonNegConstraint() : Constraint() {}
    virtual bool check(const DGP_FP& value) const override { return value >= 0; }
    virtual std::string description() const override 
        { return "[0, ∞)"; }
    virtual std::string shortID() const override { return description(); }
};
#endif

int main (int argc, char const* argv[])
{
    TCLAP::CmdLine cmd("dgp project: Remeshing tool", ' ');
    TCLAP::ValueArg<std::string> input_fname("i", "input", "Path to input mesh", true,
                                             "", "off-file", cmd);
    TCLAP::ValueArg<std::string> output_fname("o", "output", "Path for output(s)", false,
                                              "./out.off", "off-file", cmd);
    TCLAP::ValueArg<std::string> boundary_fname("b", "boundary", "Path to file defining boundary edges as indexed in input file, one per line",
                                                false, "", "boundaries-file", cmd);
    TCLAP::ValueArg<size_t> n_iters("n", "iterations", "Number of iterations (default: 20)",
                                    false, 20, "N", cmd);
    TCLAP::ValueArg<size_t> intermediates("", "intermediates", "How often to output intermediate meshes (default: don't)",
                                          false, 0, "N", cmd);
#ifndef DGP_FORCE_COLINEAR
//    std::vector<DGP_FP> values{0,1,2};
//    TCLAP::ValuesConstraint<DGP_FP> constraint(values);
    NonNegConstraint constraint;
    TCLAP::ValueArg<DGP_FP> colinearity("", "colinearity", "How much edges are allowed to deviate from colinearity and still be joined (default: " str(DEFAULT_COLINEARITY) ")",
                                       false, DEFAULT_COLINEARITY, &constraint, cmd);
#endif
    cmd.parse(argc, argv);

#ifdef DGP_FORCE_COLINEAR
    const static DGP_FP colinear_factor = 0;
#else
    const static DGP_FP colinear_factor = colinearity.getValue();
#endif

    TMesh mesh(input_fname.getValue());
    if (boundary_fname.isSet()) mesh.mark_bounds(boundary_fname.getValue());
    if (n_iters.getValue() == 0) {
        mesh.save(output_fname.getValue());
#ifndef NDEBUG
        std::cout << "WARNING: iterations=0! copying input file to output destination" << std::endl;
#endif
        return 0;
    }
    
    mesh.remesh(colinear_factor);
    for (size_t iter=1; iter<n_iters.getValue(); ++iter) {
        if (intermediates.getValue() && (iter%intermediates.getValue()) == 0)
            mesh.save(output_fname.getValue() + "." + std::to_string(iter+1));
        mesh.remesh(colinear_factor);
    }
    
    mesh.save(output_fname.getValue());
    
    return 0;
}
