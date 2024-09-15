add_library(common INTERFACE)
target_include_directories(common INTERFACE ${CMAKE_CURRENT_LIST_DIR})
#target_link_libraries(common INTERFACE spdlog::spdlog gtest::gtest)

#add_library(enableRuntime INTERFACE)
#target_compile_definitions(enableRuntime INTERFACE ENABLE_RUNTIME_ALGORITHM)
