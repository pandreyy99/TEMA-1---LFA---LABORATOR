cmake_minimum_required(VERSION 3.9)
project(LFA)

set(CMAKE_CXX_STANDARD 11)

add_executable(LFA main.cpp cmake-build-debug/AFN.cpp cmake-build-debug/AFN.h)