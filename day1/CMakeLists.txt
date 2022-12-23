add_subdirectory(common)

add_executable(d1p1 d1p1.cpp)
target_link_libraries(d1p1 PRIVATE day1-common)
