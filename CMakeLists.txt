cmake_minimum_required(VERSION 3.23)
project(SugarCLI)

set(CMAKE_CXX_STANDARD 20)

file(GLOB_RECURSE SOURCES "lib/*.cpp")
add_library(SugarCLI SHARED ${SOURCES})
