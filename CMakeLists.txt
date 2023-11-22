cmake_minimum_required(VERSION 3.12)
project(MazeSolver)

file(GLOB SOURCES "src/*.cc")

include_directories(include)

add_executable(MazeSolver ${SOURCES})
