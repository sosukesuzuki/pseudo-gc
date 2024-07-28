cmake_minimum_required(VERSION 3.0)

project(PseudoGC
        VERSION 1.0
        DESCRIPTION "Pseudo GC")

set(CMAKE_CXX_STANDARD 20)

add_executable(pgc
               src/pgc.cpp
               src/cell.cpp
               src/allocator.cpp
               src/pseudo-mutator.cpp)


target_include_directories(pgc PRIVATE src)
