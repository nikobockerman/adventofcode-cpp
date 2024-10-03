#set(problemDays 1 2 3 4 5 6)
set(problemDays 1 2)
set(testDays 1)
#set(testDays 1 2 3 4 5 6)

foreach(day IN LISTS problemDays)
  add_solution_library(solutionLib ${day})
  target_link_libraries(${solutionLib} PRIVATE tools)

  configure_file(
    input-d${day}.txt
    ${CMAKE_CURRENT_BINARY_DIR}/../share/${CMAKE_PROJECT_NAME}/inputs/y2022/input-d${day}.txt
    COPYONLY
  )

  list(FIND testDays ${day} index)
  if(index GREATER -1)
    add_input_library(inputName ${day})
    add_solution_test_executable(testName ${day})
    gtest_discover_tests(${testName})
    target_link_libraries(
      ${testName}
      PRIVATE
        ${solutionLib}
        ${inputName}
        result-type
        test-tools
        GTest::gtest_main
    )
  endif()
endforeach()
