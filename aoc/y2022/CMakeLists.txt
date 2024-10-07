set(problemDays 1 2 3 4 5 6)
set(testDays 1 2 3 4 5 6)

foreach(day IN LISTS problemDays)
    add_input_library(inputName ${day})
    add_solution_library(solutionName ${day})
    target_link_libraries(
        ${solutionName}
        PRIVATE
            day-interface
            result-type
            tools
    )

    list(FIND testDays ${day} index)
    if(index GREATER -1)
        add_solution_test_executable(testName ${day} ${inputLibName})
        gtest_discover_tests(${testName})
        target_link_libraries(
            ${testName}
            PRIVATE
                ${solutionName}
                ${inputName}
                day-interface
                test-tools
                GTest::gtest_main
        )
    endif()
endforeach()
