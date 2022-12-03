project(Potential)

set(CMAKE_CXX_STANDARD 20)
#set(CMAKE_OSX_ARCHITECTURES "arm64")
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O0 -fno-omit-frame-pointer -mno-omit-leaf-frame-pointer")

add_library(Potential STATIC System.cpp Flow.cpp)
target_include_directories(Potential PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

set(POTENTIAL_TEST_SOURCE
        ${CMAKE_CURRENT_SOURCE_DIR}/tests/Test_Config.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/tests/Test_System.cpp
        #        ${CMAKE_CURRENT_SOURCE_DIR}/tests/Test_with_Source.cpp
        #        ${CMAKE_CURRENT_SOURCE_DIR}/tests/Test_Flow.cpp
        #        ${CMAKE_CURRENT_SOURCE_DIR}/tests/1_plus_1_N=2.cpp
        #        ${CMAKE_CURRENT_SOURCE_DIR}/tests/Get_Test_Data.cpp
        #        ${CMAKE_CURRENT_SOURCE_DIR}/tests/Test_multiple_1_plus_1_flows.cpp
        CACHE INTERNAL "")

set(POTENTIAL_TEST_INCLUDE
        ${CMAKE_CURRENT_SOURCE_DIR}/tests/include
        CACHE INTERNAL "")