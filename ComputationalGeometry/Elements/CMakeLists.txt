cmake_minimum_required(VERSION 3.18)
project(Elements)

set(CMAKE_CXX_STANDARD 20)

add_library(Elements Elements.cpp Elements.h CartesianPoint2D.cpp CartesianPoint2D.h PolarPoint2D.cpp PolarPoint2D.h CartesianLine2D.cpp CartesianLine2D.h)