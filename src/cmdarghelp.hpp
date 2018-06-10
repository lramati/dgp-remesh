#ifndef __CMDARGHELP_H__
#define __CMDARGHELP_H__

#include "types.hpp"
#include "tclap/CmdLine.h"
#include <string>
#ifdef NO_FS
#include <fstream>
#else
#include FS_INC /* set to <[experimental/]filesystem> as needed in types.hpp */
#endif

#ifndef DGP_FORCE_COLINEAR
class NonNegConstraint : public TCLAP::Constraint<DGP_FP> {
public:
    NonNegConstraint() : Constraint() {}
    virtual bool check(const DGP_FP& value) const override { return value >= 0; }
    virtual std::string description() const override 
        { return "[0, ∞)"; }
    virtual std::string shortID() const override { return description(); }
};
#endif


class FileExistsConstraint : public TCLAP::Constraint<std::string> {
private:
    std::string desc;
public:
    FileExistsConstraint(const std::string& extension="") : Constraint() {
        if (extension.empty()) desc = "existing filepath";
        else desc = "path to existing " + extension + " file";
    }
    virtual bool check(const std::string& value) const override {
#ifdef NO_FS
#   ifndef NDEBUG
        std::cerr << "Warning: Using ifstream instead of filesystem to check file existence" << std::endl;
#   endif
        return !std::ifstream(value).fail();
#else
        return FS_NS::exists(FS_NS::path(value));
#endif
    }
    virtual std::string description() const override {
        return desc;
    }
    virtual std::string shortID() const override {
        return description();
    }
};

#endif /* __CMDARGHELP_H__ */
