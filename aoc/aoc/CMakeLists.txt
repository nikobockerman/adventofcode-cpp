cmake_path(RELATIVE_PATH
    CMAKE_INSTALL_FULL_DATADIR
    BASE_DIRECTORY ${CMAKE_INSTALL_FULL_BINDIR}
    OUTPUT_VARIABLE binToDataPath
)
configure_file(aoc-config.in.hpp aoc-config.hpp @ONLY)

add_executable(aoc main.cpp)
target_include_directories(aoc PRIVATE ${CMAKE_CURRENT_BINARY_DIR})
target_link_libraries(
    aoc
    PRIVATE
        y2022-d1-solution
        y2022-d2-solution
        Boost::dll
        fmt::fmt
        spdlog::spdlog
)
