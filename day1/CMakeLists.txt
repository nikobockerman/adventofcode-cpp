add_input_library(d1-input input)

add_executable(d1p1 d1p1.cpp)
target_link_libraries(d1p1 PRIVATE common d1-input)
target_compile_options(d1p1 PRIVATE "/constexpr:steps2097152")

add_executable(d1p2 d1p2.cpp)
target_link_libraries(d1p2 PRIVATE common d1-input)
target_compile_options(d1p2 PRIVATE "/constexpr:steps2097152")
