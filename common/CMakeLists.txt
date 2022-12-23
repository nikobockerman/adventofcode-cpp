add_library(common file-reader.cpp program.cpp)
target_include_directories(common PUBLIC ${CMAKE_CURRENT_LIST_DIR})
target_link_libraries(common PUBLIC
    Boost::program_options
    spdlog::spdlog
)
