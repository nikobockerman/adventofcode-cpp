add_executable(common-tests test-main.cpp test-utils.cpp)
target_link_libraries(common-tests PRIVATE common GTest::gmock)
gtest_discover_tests(common-tests)
