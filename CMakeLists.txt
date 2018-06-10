project(dgp-remesh)

set(CMAKE_EXPORT_COMPILE_COMMANDS 1)
#set(CMAKE_VERBOSE_MAKEFILE on)

include(CheckCXXCompilerFlag)
CHECK_CXX_COMPILER_FLAG("-std=c++17" COMPILER_SUPPORTS_CXX17)
CHECK_CXX_COMPILER_FLAG("-std=c++14" COMPILER_SUPPORTS_CXX14)
CHECK_CXX_COMPILER_FLAG("-std=c++11" COMPILER_SUPPORTS_CXX11)
if (COMPILER_SUPPORTS_CXX17)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")
elseif(COMPILER_SUPPORTS_CXX14)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")
    message(WARNING "Falling back to c++14")
elseif(COMPILER_SUPPORTS_CXX11)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
    message(WARNING "Falling back to c++11")
else()
    message(FATAL_ERROR "No modern C++ standards supported (Minimum C++11)")
endif()

option(DGP_NO_ARRAYS "Disable std::array/std::initializer_list integration" OFF)
if(DGP_NO_ARRAYS)
    add_definitions(-DDGP_NO_ARRAYS)
endif()
option(DGP_STRICT_MEMORY "Disable potentially dangerous memory access" OFF)
if(DGP_STRICT_MEMORY)
    add_definitions(-DDGP_STRICT_MEMORY)
endif()

set(DGP_CPP
    src/dgp-remesh.cpp)

set(DGP_HPP
    src/vertex.hpp
    src/trimesh.hpp)

add_executable(dgp-remesh ${DGP_CPP} ${DGP_HPP})
include_directories(third-party)
