add_subdirectory(common)

add_executable(day1 day1.cpp)
target_link_libraries(day1 PRIVATE day1-common)
