project(Graph)

set(CMAKE_CXX_STANDARD 20)

add_library(Graph_lib STATIC Graph.cpp Leaf.cpp)
target_include_directories(Graph_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

set(GRAPH_TEST_SOURCE ${CMAKE_CURRENT_SOURCE_DIR}/tests/LeaveTest.cpp CACHE INTERNAL "")

