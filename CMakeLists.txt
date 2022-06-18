cmake_minimum_required(VERSION 3.22)
project(lrn-gen)

set(CMAKE_CXX_STANDARD 23)

add_executable(lrn-gen src/lrn-gen/entry/entry.cxx)
set_target_properties(lrn-gen PROPERTIES LINKER_LANGUAGE CXX)

target_include_directories(lrn-gen PUBLIC src/)

add_subdirectory(src)