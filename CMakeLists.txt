project(dgp-remesh)

set(CMAKE_EXPORT_COMPILE_COMMANDS 1)
#set(CMAKE_VERBOSE_MAKEFILE on)

include(CheckCXXCompilerFlag)
CHECK_CXX_COMPILER_FLAG("-std=c++17" COMPILER_SUPPORTS_CXX17)
CHECK_CXX_COMPILER_FLAG("-std=c++14" COMPILER_SUPPORTS_CXX14)
if (COMPILER_SUPPORTS_CXX17)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")
elseif(COMPILER_SUPPORTS_CXX14)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")
    message(WARNING "Falling back to c++14")
    add_definitions(-DNO_CXX17)
else()
    message(FATAL_ERROR "No modern C++ standards supported (Minimum C++14)")
endif()

option(DGP_NO_ARRAYS "Disable std::array/std::initializer_list integration" OFF)
if(DGP_NO_ARRAYS)
    add_definitions(-DDGP_NO_ARRAYS)
endif()
option(DGP_STRICT_MEMORY "Disable potentially dangerous memory access" OFF)
if(DGP_STRICT_MEMORY)
    add_definitions(-DDGP_STRICT_MEMORY)
endif()
option(DGP_USE_DOUBLE "Use doubles instead of floats for floating-point operations" OFF)
if(DGP_USE_DOUBLE)
    add_definitions(-DDGP_USE_DOUBLE)
endif()
option(DGP_FORCE_COLINEAR "Only merge short edges if they are exactly colinear" OFF)
if(DGP_FORCE_COLINEAR)
    add_definitions(-DDGP_FORCE_COLINEAR)
endif()

set(DGP_CPP
    src/dgp-remesh.cpp
    src/trimesh.cpp)

set(DGP_HPP
    src/vertex.hpp
    src/trimesh.hpp
    src/cmdarghelp.hpp
    src/types.hpp)

add_executable(dgp-remesh ${DGP_CPP} ${DGP_HPP})
include_directories(third-party)
