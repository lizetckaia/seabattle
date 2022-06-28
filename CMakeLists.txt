cmake_minimum_required(VERSION 3.21)
project(untitled1)

set(CMAKE_CXX_STANDARD 14)

add_subdirectory(external/doctest)
add_executable(untitled1 main.cpp external/doctest/doctest.cpp external/doctest/doctest.h funtionfortest.cpp)

enable_testing()

add_executable(untitled1_tests tests.cpp)
target_link_libraries(untitled1_tests PUBLIC doctest)

add_test(NAME test COMMAND test --force-colors -d)
add_custom_target(cloud-test COMMAND test --force-colors -d)