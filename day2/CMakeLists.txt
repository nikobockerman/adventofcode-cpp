add_subdirectory(common)

add_executable(d2p1 d2p1.cpp)
target_link_libraries(d2p1 PRIVATE common day2-common)

add_executable(d2p2 d2p2.cpp)
target_link_libraries(d2p2 PRIVATE common day2-common)
