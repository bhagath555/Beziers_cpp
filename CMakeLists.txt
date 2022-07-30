cmake_minimum_required(VERSION 3.23)
project(Bezier)

## This directory will be the final dir
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ..)

# To add pubind11 functions.
find_package(pybind11 REQUIRED)

add_subdirectory (binding)