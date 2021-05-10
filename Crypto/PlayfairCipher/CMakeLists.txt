cmake_minimum_required(VERSION 3.20)
project(PlayfairCipher)

set(CMAKE_CXX_STANDARD 20)

include_directories(../CaesarCipher)

set(EXT_LIB_BUILD_TYPE "release")

if (EXT_LIB_BUILD_TYPE STREQUAL "Debug")
    set(EXT_LIB_BUILD_TYPE "debug")
endif ()

add_subdirectory(../CaesarCipher ../../CaesarCipher/cmake-build-${EXT_LIB_BUILD_TYPE})

add_executable(${PROJECT_NAME} main.cpp)

target_link_libraries(${PROJECT_NAME} CaesarCipherImpl)