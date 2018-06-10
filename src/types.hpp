#ifndef __TYPES_H__
#define __TYPES_H__

// precision type
#ifdef DGP_USE_DOUBLE
#define DGP_FP double
#else
#define DGP_FP float
#endif

// vertex container type
#include <forward_list>
#define DGP_VERT_CON std::forward_list<Vertex>
#define DGP_VERT_ITR DGP_VERT_CON::iterator

// filesystem support
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

// constants
#define TOSTR(s) TOSTRH(s)
#define TOSTRH(s) #s
#define DEFAULT_COLINEARITY 0.05

#endif /*__TYPES_H__*/
