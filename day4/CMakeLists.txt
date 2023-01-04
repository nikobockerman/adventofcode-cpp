add_input_library(d4-input input)

add_executable(d4p1 d4p1.cpp)
target_link_libraries(d4p1 PRIVATE common d4-input)
target_compile_options(d4p1 PRIVATE "/constexpr:steps4194304")

add_executable(d4p2 d4p2.cpp)
target_link_libraries(d4p2 PRIVATE common d4-input)
target_compile_options(d4p2 PRIVATE "/constexpr:steps4194304")
