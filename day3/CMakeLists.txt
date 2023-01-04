add_input_library(d3-input input)

add_executable(d3p1 d3p1.cpp)
target_link_libraries(d3p1 PRIVATE common d3-input enableRuntime)

add_executable(d3p2 d3p2.cpp)
target_link_libraries(d3p2 PRIVATE common d3-input enableRuntime)
