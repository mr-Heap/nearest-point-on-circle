cmake_minimum_required(VERSION 3.28)
project(nearest_point_on_circle)

set(CMAKE_CXX_STANDARD 17)

enable_testing()

add_subdirectory(googletest)

add_executable(nearest_point_on_circle src/main.cpp
        include/geometry.h
        src/geometry.cpp
        tests/test.cpp)

target_link_libraries(nearest_point_on_circle GTest::gtest GTest::gtest_main)

add_test(NAME tests COMMAND symmetric-polygon)


