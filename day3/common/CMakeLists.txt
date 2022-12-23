add_library(day3-common day3-common.cpp)
target_include_directories(day3-common PUBLIC ${CMAKE_CURRENT_LIST_DIR})
target_link_libraries(day3-common PRIVATE
    common
    fmt::fmt
    spdlog::spdlog
)
