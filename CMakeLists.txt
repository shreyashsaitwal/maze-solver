cmake_minimum_required(VERSION 3.12)
project(maze-solver)

file(GLOB SOURCES "src/*.cc")

include_directories(include)

add_executable(maze-solver ${SOURCES})
