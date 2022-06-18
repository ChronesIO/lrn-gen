cmake_minimum_required(VERSION 3.22)
project(lrn)

set(CMAKE_CXX_STANDARD 23)

add_library(lrn src/lrn)
set_target_properties(lrn PROPERTIES LINKER_LANGUAGE CXX)

target_include_directories(lrn PUBLIC src/)

add_subdirectory(src)
