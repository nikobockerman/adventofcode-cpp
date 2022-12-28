add_subdirectory(test)

add_library(common program.cpp utils.cpp)
target_include_directories(common PUBLIC ${CMAKE_CURRENT_LIST_DIR})
target_link_libraries(common PUBLIC
    Boost::program_options
    spdlog::spdlog
)
