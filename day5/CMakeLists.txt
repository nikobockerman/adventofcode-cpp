add_input_library(d5-input input)

add_executable(d5p1 d5p1.cpp)
target_link_libraries(d5p1 PRIVATE common d5-input enableRuntime)
