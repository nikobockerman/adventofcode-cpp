add_solution_library(name 2022-day1.cpp)
target_compile_options(${name} PRIVATE "/constexpr:steps2000000")
#target_link_libraries(${name} PRIVATE enableRuntime)
