cmake_minimum_required(VERSION 3.22)
project(Simulation)

set(CMAKE_CXX_STANDARD 20)

add_subdirectory(Libraries/GraphLibrary)
add_subdirectory(Libraries/Potential)
add_subdirectory(Libraries/googletest)

add_executable(Simulation main.cpp)

set(LIBRARIES "Graph_lib")

target_link_libraries(Simulation ${LIBRARIES})

set(TEST_SOURCE ${GRAPH_TEST_SOURCE})

add_executable(Test ${TEST_SOURCE})
target_link_libraries(Test ${LIBRARIES})
target_link_libraries(Test gtest gtest_main)
