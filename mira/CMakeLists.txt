cmake_minimum_required (VERSION 3.0.2)
project (mira)
enable_testing ()

include(FindBoost)

add_library (mira ./src/language.cpp ./src/functions.cpp)
target_include_directories (mira PRIVATE ./include)
target_include_directories (sdl-plus-plus PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include/>
)

if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU" OR
    "${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
  target_compile_options (mira PRIVATE -Wall -Wextra -pedantic -Werror)
endif()

find_package(Boost 1.61 REQUIRED COMPONENTS unit_test_framework)

function(add_test_file filename)
  add_executable(${filename} tests/${filename})
  target_link_libraries(${filename} PRIVATE mira)
  target_compile_definitions(${filename} PRIVATE "BOOST_TEST_DYN_LINK=1")
  target_link_libraries(${filename} PRIVATE ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY})
  target_include_directories(${filename} PRIVATE ${Boost_INCLUDE_DIRS})
  add_test(${filename} ${filename})
endfunction(add_test_file)

add_test_file(adjacent_for_each_test.cpp)
add_test_file(chained_test.cpp)
add_test_file(function_definition_test.cpp)
add_test_file(functions_visible_inside_body_test.cpp)
add_test_file(optionally_find_if_test.cpp)
add_test_file(function_call_with_parameters_test.cpp)
add_test_file(function_doesnt_exist_test.cpp)
add_test_file(shadowing_test.cpp)
add_test_file(redefining_existing_function_test.cpp)

