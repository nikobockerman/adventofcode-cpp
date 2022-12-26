add_subdirectory(common)

add_executable(d3p1 d3p1.cpp)
target_link_libraries(d3p1 PRIVATE common day3-common)

add_executable(d3p2 d3p2.cpp)
target_link_libraries(d3p2 PRIVATE common day3-common)

configure_file(input input COPYONLY)
