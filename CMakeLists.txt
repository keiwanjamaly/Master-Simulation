cmake_minimum_required(VERSION 3.22)
project(Simulation)

set(CMAKE_CXX_STANDARD 20)

add_subdirectory(Libraries/GraphLibrary)
add_subdirectory(Libraries/Potential)

set(TEST_SOURCE ${GRAPH_TEST_SOURCE} ${POTENTIAL_TEST_SOURCE})
set(TEST_INCLUDES ${GRAPH_TEST_INCLUDE} ${POTENTIAL_TEST_INCLUDE})
set(GLOBAL_INCLUDES ${CMAKE_CURRENT_SOURCE_DIR}/include)

set(Boost_USE_STATIC_LIBS ON)
find_package(Boost COMPONENTS unit_test_framework REQUIRED)

find_package(SUNDIALS REQUIRED)

set(LIBRARIES Graph_lib Potential ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY} SUNDIALS::cvode)


add_executable(Simulation main.cpp)
target_include_directories(Simulation PUBLIC ${GLOBAL_INCLUDES})
target_link_libraries(Simulation ${LIBRARIES})


add_executable(Test test.cpp ${TEST_SOURCE})
target_include_directories(Test PUBLIC ${TEST_INCLUDES} ${GLOBAL_INCLUDES})
target_link_libraries(Test ${LIBRARIES})
target_link_libraries(Test simdjson)