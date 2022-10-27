project(Potential)

set(CMAKE_CXX_STANDARD 20)
#
#find_package(Boost REQUIRED)

add_library(Potential STATIC Solver.cpp)
target_include_directories(Potential PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

set(POTENTIAL_TEST_SOURCE
        ${CMAKE_CURRENT_SOURCE_DIR}/tests/Test_System.cpp
        CACHE INTERNAL "")

set(POTENTIAL_TEST_INCLUDE
        ${CMAKE_CURRENT_SOURCE_DIR}/tests/include
        CACHE INTERNAL "")