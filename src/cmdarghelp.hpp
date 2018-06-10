#ifndef __CMDARGHELP_H__
#define __CMDARGHELP_H__

#include <string>
#ifdef NO_CXX17
#   include <fstream>
#else
#   include <filesystem>
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
#ifdef NO_CXX17
        return !std::ifstream(value).fail();
#else
        return std::exists(std::path(value));
#endif
    }
    virtual std::string description() const override {
        return desc;
    }
    virtual std::string shortID() const override {
        return description();
    }
};

