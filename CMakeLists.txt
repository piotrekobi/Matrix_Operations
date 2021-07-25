cmake_minimum_required(VERSION 3.19)
set (CMAKE_CXX_STANDARD 11)
project("Matrix_Operations")

include_directories(src)
enable_testing()

add_subdirectory(src)
add_subdirectory(test)
