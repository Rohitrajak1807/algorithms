cmake_minimum_required(VERSION 3.18)
project(Elements)

set(CMAKE_CXX_STANDARD 20)

add_library(Elements CartesianPoint2D.cpp PolarPoint2D.cpp CartesianLine2D.cpp Elements.cpp Elements.h CartesianLine2D.h CartesianPoint2D.h PolarPoint2D.h)
