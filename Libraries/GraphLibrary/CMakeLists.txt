project(Graph)

set(GRAPH_INCLUDES
        ${CMAKE_CURRENT_SOURCE_DIR}/include
        CACHE INTERNAL "")

set(GRAPH_TEST_SOURCE
        ${CMAKE_CURRENT_SOURCE_DIR}/tests/Tree.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/tests/TreeWithNeighbours.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/tests/TreeWithCoordinates.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/tests/TreeWithData.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/tests/TreeWithComparisons.cpp
        #        ${CMAKE_CURRENT_SOURCE_DIR}/tests/LeafTest.cpp
        #        ${CMAKE_CURRENT_SOURCE_DIR}/tests/LeafIntegrationTest.cpp
        #        ${CMAKE_CURRENT_SOURCE_DIR}/tests/LeafTestOnData.cpp
        #        ${CMAKE_CURRENT_SOURCE_DIR}/tests/PlotCalculationTest.cpp
        #        ${CMAKE_CURRENT_SOURCE_DIR}/tests/LeafTestBlockedTiles.cpp
        CACHE INTERNAL "")

set(GRAPH_TEST_INCLUDE
        ${CMAKE_CURRENT_SOURCE_DIR}/tests/include
        CACHE INTERNAL "")

