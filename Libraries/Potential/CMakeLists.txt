project(Potential)

set(POTENTIAL_INCLUDES
        ${CMAKE_CURRENT_SOURCE_DIR}/include
        CACHE INTERNAL "")

set(POTENTIAL_TEST_SOURCE
        ${CMAKE_CURRENT_SOURCE_DIR}/tests/Test_Config.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/tests/Test_System.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/tests/Test_with_Source.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/tests/Test_Flow.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/tests/1_plus_1_N=2.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/tests/Get_Test_Data.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/tests/Test_multiple_1_plus_1_flows.cpp
        CACHE INTERNAL "")

set(POTENTIAL_TEST_INCLUDE
        ${CMAKE_CURRENT_SOURCE_DIR}/tests/include
        CACHE INTERNAL "")