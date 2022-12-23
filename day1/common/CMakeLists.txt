add_library(day1-common day1-common.cpp)
target_include_directories(day1-common PUBLIC ${CMAKE_CURRENT_LIST_DIR})
target_link_libraries(day1-common PRIVATE
    common
    fmt::fmt
    spdlog::spdlog
)
