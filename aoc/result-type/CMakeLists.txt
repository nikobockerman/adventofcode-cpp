add_library(result-type INTERFACE)
target_include_directories(result-type INTERFACE ${CMAKE_CURRENT_LIST_DIR})
target_link_libraries(result-type INTERFACE fmt::fmt)
