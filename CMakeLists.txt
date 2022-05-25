cmake_minimum_required(VERSION 3.20)
project(InputRumbleReport)

set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")
include(Init_project)
include(Import_node)
include(Import_vcpkg)

add_subdirectory(mupen64plus-input-sdl)
add_subdirectory(helper)
