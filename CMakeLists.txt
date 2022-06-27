cmake_minimum_required(VERSION 3.21)
project(untitled1)

set(CMAKE_CXX_STANDARD 14)

add_executable(untitled1 main.cpp)

enable_testing()

add_executable(untitled1_doctest doctest.h)
add_executable(untitled1_tests tests.cpp)
target_link_libraries(untitled1_tests PUBLIC doctest)
