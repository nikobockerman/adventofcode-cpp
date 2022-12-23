add_library(day2-common day2-common.cpp)
target_include_directories(day2-common PUBLIC ${CMAKE_CURRENT_LIST_DIR})
target_link_libraries(day2-common PRIVATE
    common
    spdlog::spdlog
)
