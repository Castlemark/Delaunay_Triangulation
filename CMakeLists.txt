cmake_minimum_required(VERSION 3.9)
project(Delaunay_Triangulation)

set(CMAKE_CXX_STANDARD 14)
SET(GCC_COVERAGE_COMPILE_FLAGS "-Wno-narrowing")

add_executable(Delaunay_Triangulation
        ClassDiagram.cd
        Delaunay.cpp
        Delaunay.h
        input.txt
        main.cpp
        Mesh.cpp
        Mesh.h
        Parser.cpp
        Parser.h)
