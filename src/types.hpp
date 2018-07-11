#ifndef __TYPES_H__
#define __TYPES_H__

// precision type
#ifdef DGP_USE_DOUBLE
#define DGP_FP double
#else
#define DGP_FP float
#endif

// vertex container type (Still not sold, want it to be easy to change)
#include <forward_list>
#define DGP_VERT_CON std::forward_list<Vertex>
#define DGP_VERT_ITR DGP_VERT_CON::iterator

#include <set>
#define DGP_EDGE_CON std::multiset<Edge*, EdgeLenSort>
#define DGP_EDGE_ITR DGP_EDGE_CON::iterator

// filesystem support (for loading/saving meshes
#ifdef NO_CXX17
#   define NO_FS
#else
#   if __has_include(<filesystem>)
#       define FS_INC <filesystem>
#       define FS_NS std::filesystem
#   elif __has_include(<experimental/filesystem>)
#       define FS_INC <experimental/filesystem>
#       define FS_NS std::experimental::filesystem
#   else
#       define NO_FS
#   endif
#endif

// constants that have yet to be nailed down
#define TOSTR(s) TOSTRH(s)
#define TOSTRH(s) #s

// useful types
struct Vec2 {
    /* Members */
    DGP_FP x,y;
    
    /* Constructors */
    Vec2(DGP_FP x_, DGP_FP y_) : x(x_), y(y_) {}
    Vec2() : Vec2(0.f,0.f) {}
    Vec2(const Vec2& rhs) = default;
    Vec2(Vec2&& rhs) = default;
    
    /* Utility Accessors */
#ifndef GDP_STRICT_MEMORY
    operator DGP_FP*() { return &x; }
    operator const DGP_FP*() const { return &x; }
#endif
    DGP_FP& operator[](size_t index);
    const DGP_FP& operator[](size_t index) const;
    friend std::istream& operator>>(std::istream& is, Vec2& v);
    
    /* Array Interface */
#ifndef DGP_NO_ARRAYS
    Vec2(std::array<DGP_FP, 2> xyz) : Vec2(xyz[0], xyz[1]) {}
#endif
};

struct Vec3 {
    /* Members */
    DGP_FP x,y,z;
    
    /* Constructors */
    Vec3(DGP_FP x_, DGP_FP y_, DGP_FP z_) : x(x_), y(y_), z(z_) {}
    Vec3() : Vec3(0.f,0.f,0.f) {}
    Vec3(const Vec3& rhs) = default;
    Vec3(Vec3&& rhs) = default;
    
    /* Utility Accessors */
#ifndef GDP_STRICT_MEMORY
    operator DGP_FP*() { return &x; }
    operator const DGP_FP*() const { return &x; }
#endif
    DGP_FP& operator[](size_t index);
    const DGP_FP& operator[](size_t index) const;
    
    /* Other Operators */
    Vec3 operator-(const Vec3& rhs) const { return {x-rhs.x,y-rhs.y,z-rhs.z}; }
    Vec3 operator-() const { return {-x, -y, -z }; };
    friend std::istream& operator>>(std::istream& is, Vec3& v);
    
    /* Array Interface */
#ifndef DGP_NO_ARRAYS
    Vec2(std::array<DGP_FP, 3> xyz) : Vec2(xyz[0], xyz[1], xyz[2]) {}
#endif
};

#endif /*__TYPES_H__*/
