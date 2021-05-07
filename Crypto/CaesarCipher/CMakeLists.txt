cmake_minimum_required(VERSION 3.19)
project(CaesarCipher)

set(CMAKE_CXX_STANDARD 20)

add_library(CaesarCipherImpl caesar_cipher.cpp caesar_cipher.h)

add_executable(CaesarCipher main.cpp)

target_link_libraries(CaesarCipher CaesarCipherImpl)