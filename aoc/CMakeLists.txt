function(set_year_part)
  cmake_path(GET CMAKE_CURRENT_LIST_DIR FILENAME yearPart)
  set(yearPart ${yearPart} PARENT_SCOPE)
endfunction()

function(set_day_part day)
  set(dayPart d${day} PARENT_SCOPE)
endfunction()

function(add_input_library targetNameVariable day)
  set_year_part()
  set_day_part(${day})

  set(inputFile input-${dayPart}.txt)
  file(READ ${inputFile} inputString)
  configure_file(${CMAKE_CURRENT_FUNCTION_LIST_DIR}/input.in.hpp inputLib/${dayPart}/input.hpp @ONLY)

  set(targetName ${yearPart}-${dayPart}-input)
  add_library(${targetName} INTERFACE)
  target_include_directories(${targetName} INTERFACE ${CMAKE_CURRENT_BINARY_DIR}/inputLib/${dayPart})
  set(${targetNameVariable} ${targetName} PARENT_SCOPE)
endfunction()

function(add_solution_library targetNameVariable day)
  set_year_part()
  set_day_part(${day})

  configure_file(
    ${CMAKE_CURRENT_FUNCTION_LIST_DIR}/day-interface.in.hpp
    dayInterfaceLib/${dayPart}/day-interface-${yearPart}-${dayPart}.hpp
    @ONLY
  )

  set(sourceFile ${dayPart}.cpp)

  set(targetName ${yearPart}-${dayPart}-solution)
  add_library(${targetName} STATIC ${sourceFile})
  target_include_directories(${targetName} PUBLIC ${CMAKE_CURRENT_BINARY_DIR}/dayInterfaceLib/${dayPart})
  target_link_libraries(${targetName} PUBLIC result-type)
  set(${targetNameVariable} ${targetName} PARENT_SCOPE)
endfunction()

function(add_solution_test_executable targetNameVariable day)
  set_year_part()
  set_day_part(${day})
  set(sourceFile ${dayPart}.test.cpp)

  set(targetName ${yearPart}-${dayPart}-test)
  add_executable(${targetName} ${sourceFile})
  set(${targetNameVariable} ${targetName} PARENT_SCOPE)
endfunction()

add_subdirectory(result-type)
add_subdirectory(test-tools)
add_subdirectory(tools)
add_subdirectory(y2022)
