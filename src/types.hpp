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

// constants
#define str(s) xstr(s)
#define xstr(s) #s
#define DEFAULT_COLINEARITY 0.05

#endif /*__TYPES_H__*/
