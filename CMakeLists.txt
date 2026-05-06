cmake_minimum_required(VERSION 3.10)
project(sorting_algorithms)

add_library(sorting_algorithms_lib INTERFACE)
target_include_directories(sorting_algorithms_lib INTERFACE include/)

add_executable(test_sorting_algorithms
        src/test_sorting_algorithms.cpp)

target_link_libraries(test_sorting_algorithms sorting_algorithms_lib)

add_executable(efficiency_tests
        src/main.cpp)
target_link_libraries(efficiency_tests sorting_algorithms_lib)
