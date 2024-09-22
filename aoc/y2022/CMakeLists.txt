set(problemDays 1 2 3 4 5 6)

foreach(day IN LISTS problemDays)
    add_solution_library(name d${day}.cpp)
endforeach()
