set(name problem-2022-day1)
add_library(${name} SHARED 2022-day1.cxx)
target_sources(${name} PUBLIC FILE_SET CXX_MODULES FILES 2022-day1.cxx)
target_link_libraries(${name} PRIVATE common)
