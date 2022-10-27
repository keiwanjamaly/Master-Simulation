cmake_minimum_required(VERSION 3.22)
project(Simulation)

set(CMAKE_CXX_STANDARD 20)

add_subdirectory(Libraries/GraphLibrary)
add_subdirectory(Libraries/Potential)
add_subdirectory(Libraries/googletest)

#set(Boost_INCLUDE_DIRS Libraries/odeint/include CACHE PATH "")
#include_directories(Libraries/odeint/include)

#message(PROJECT_SOURCE_DIR="${PROJECT_SOURCE_DIR}")
#message(Boost_INCLUDE_DIRS="${Boost_INCLUDE_DIRS}")

set(TEST_SOURCE ${GRAPH_TEST_SOURCE} ${POTENTIAL_TEST_SOURCE})
set(TEST_INCLUDES ${GRAPH_TEST_INCLUDE} ${POTENTIAL_TEST_INCLUDE})

set(LIBRARIES Graph_lib Potential)


add_executable(Simulation main.cpp)
target_link_libraries(Simulation ${LIBRARIES})


add_executable(Test ${TEST_SOURCE})
target_include_directories(Test PUBLIC ${TEST_INCLUDES})
target_link_libraries(Test ${LIBRARIES})
target_link_libraries(Test gtest gtest_main)
