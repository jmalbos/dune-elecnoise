## Setup the project
cmake_minimum_required(VERSION 3.0 FATAL_ERROR)
project(DUNE_ELECNOISE)

## Find ROOT headers and libraries
find_package(ROOT)
include(${ROOT_USE_FILE})
#include_directories(${ROOT_INCLUDE_DIRS})

## Recurse through sub-directories
add_subdirectory(src)
