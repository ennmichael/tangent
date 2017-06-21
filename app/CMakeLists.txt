add_executable (app src/main.cpp)
target_include_directories (app PRIVATE ./include)

if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU" OR
    "${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
  target_compile_options (app PRIVATE -Wall -Wextra -pedantic -Werror)
endif()

target_link_libraries (app sdl-plus-plus)
