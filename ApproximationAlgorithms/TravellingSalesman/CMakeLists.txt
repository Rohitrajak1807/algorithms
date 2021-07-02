cmake_minimum_required(VERSION 3.19)
project(TravellingSalesman)

set(CMAKE_CXX_STANDARD 20)

set(EXT_LIB_BUILD_TYPE debug)

if (${CMAKE_BUILD_TYPE} STREQUAL Release)
    set(EXT_LIB_BUILD_TYPE release)
endif ()

add_executable(${PROJECT_NAME} main.cpp)
target_include_directories(${PROJECT_NAME} PRIVATE ../../Graph/JarnikPrimMST)
target_link_directories(${PROJECT_NAME} PRIVATE ../../Graph/JarnikPrimMST/cmake-build-${EXT_LIB_BUILD_TYPE})
target_link_libraries(${PROJECT_NAME} JarnikPrim)