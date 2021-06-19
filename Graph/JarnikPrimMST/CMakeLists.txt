cmake_minimum_required(VERSION 3.20)
project(JarnikPrimMST)

set(CMAKE_CXX_STANDARD 20)

add_library(JarnikPrim SHARED JarnikPrim.h JarnikPrim.cpp)

include_directories(./)

add_executable(JarnikPrimMST main.cpp)
target_link_libraries(JarnikPrimMST JarnikPrim)