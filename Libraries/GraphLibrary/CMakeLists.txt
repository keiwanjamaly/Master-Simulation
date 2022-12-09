project(Graph)

add_library(Graph_lib Leaf.cpp)
target_include_directories(Graph_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

set(GRAPH_TEST_SOURCE
        ${CMAKE_CURRENT_SOURCE_DIR}/tests/LeafTest.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/tests/LeafIntegrationTest.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/tests/LeafTestOnData.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/tests/TestData.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/tests/PlotCalculationTest.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/tests/LeafTestBlockedTiles.cpp
        CACHE INTERNAL "")

set(GRAPH_TEST_INCLUDE
        ${CMAKE_CURRENT_SOURCE_DIR}/tests/include
        CACHE INTERNAL "")

