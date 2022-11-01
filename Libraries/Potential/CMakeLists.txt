project(Potential)

set(CMAKE_CXX_STANDARD 20)
#
#find_package(Boost REQUIRED)

add_library(Potential STATIC System.cpp Flow.cpp)
target_include_directories(Potential PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

set(POTENTIAL_TEST_SOURCE
        ${CMAKE_CURRENT_SOURCE_DIR}/tests/Test_System.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/tests/Test_with_Source.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/tests/Test_Flow.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/tests/1_plus_1_MF.cpp
        CACHE INTERNAL "")

set(POTENTIAL_TEST_INCLUDE
        ${CMAKE_CURRENT_SOURCE_DIR}/tests/include
        CACHE INTERNAL "")