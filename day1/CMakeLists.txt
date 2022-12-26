add_subdirectory(common)

add_executable(d1p1 d1p1.cpp)
target_link_libraries(d1p1 PRIVATE common day1-common)

add_executable(d1p2 d1p2.cpp)
target_link_libraries(d1p2 PRIVATE common day1-common)

configure_file(input input COPYONLY)
