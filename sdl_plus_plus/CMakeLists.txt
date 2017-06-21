cmake_minimum_required (VERSION 3.0.2)
add_library (sdl-plus-plus ./src/drawing.cpp ./src/flow.cpp ./src/resource.cpp)

set (CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/find_modules)

find_package (SDL2 REQUIRED)
find_package (SDL2_image REQUIRED)

target_include_directories (sdl-plus-plus PRIVATE ${SDL2_INCLUDE_DIR})
target_include_directories (sdl-plus-plus PRIVATE ${SDL2_IMAGE_INCLUDE_DIRS})

target_include_directories (sdl-plus-plus PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include/sdl-plus-plus)
target_include_directories (sdl-plus-plus PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include/>
)

target_link_libraries (sdl-plus-plus ${SDL2_LIBRARY})
target_link_libraries (sdl-plus-plus ${SDL2_IMAGE_LIBRARIES})

if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU" OR
    "${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
  target_compile_options (sdl-plus-plus PRIVATE -Wall -Wextra -pedantic -Werror)
endif()

