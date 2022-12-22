add_executable(day1 day1.cpp)
target_link_libraries(day1 PRIVATE
    Boost::program_options
    fmt::fmt
    spdlog::spdlog
)
