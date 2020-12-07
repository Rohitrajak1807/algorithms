cmake_minimum_required(VERSION 3.19)
project(GrahamScan)

set(CMAKE_CXX_STANDARD 20)

add_executable(${PROJECT_NAME} main.cpp)

include_directories(../Elements ../Elements/cmake-build-${CMAKE_BUILD_TYPE})
add_subdirectory(../Elements Elements)
target_link_libraries(${PROJECT_NAME} Elements)