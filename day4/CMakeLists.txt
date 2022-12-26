add_subdirectory(common)

add_executable(d4p1 d4p1.cpp)
target_link_libraries(d4p1 PRIVATE common day4-common)

add_executable(d4p2 d4p2.cpp)
target_link_libraries(d4p2 PRIVATE common day4-common)

configure_file(input input COPYONLY)
