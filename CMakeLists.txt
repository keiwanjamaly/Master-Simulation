cmake_minimum_required(VERSION 3.22)
project(Simulation)

set(CMAKE_CXX_STANDARD 20)

add_executable(Simulation main.cpp Modules/Graph.cpp Modules/Graph.h Modules/Leave.cpp Modules/Leave.h Modules/Potential.cpp Modules/Potential.h Modules/Types.h)

add_subdirectory(Google_tests)