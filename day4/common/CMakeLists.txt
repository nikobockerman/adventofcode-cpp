add_library(day4-common day4-common.cpp)
target_include_directories(day4-common PUBLIC ${CMAKE_CURRENT_LIST_DIR})
target_link_libraries(day4-common PRIVATE
    common
    spdlog::spdlog
)
