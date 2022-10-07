project(Potential)

set(CMAKE_CXX_STANDARD 20)

add_library(Potential STATIC Potential.cpp)
target_include_directories(Potential PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

