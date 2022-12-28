add_executable(d5p1 d5p1.cpp)
target_link_libraries(d5p1 PRIVATE common)

configure_file(input input COPYONLY)
