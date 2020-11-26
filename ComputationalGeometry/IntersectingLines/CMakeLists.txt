cmake_minimum_required(VERSION 3.18)
project(IntersectingLines)

set(CMAKE_CXX_STANDARD 20)

add_executable(IntersectingLines main.cpp)

add_subdirectory(Elements)
target_link_libraries(${PROJECT_NAME} Elements)