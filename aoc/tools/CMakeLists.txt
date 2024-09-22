add_library(tools INTERFACE)
target_include_directories(tools INTERFACE ${CMAKE_CURRENT_LIST_DIR})
target_link_libraries(tools INTERFACE spdlog::spdlog GTest::gtest)

add_library(enableRuntime INTERFACE)
target_compile_definitions(enableRuntime INTERFACE ENABLE_RUNTIME_ALGORITHM)
