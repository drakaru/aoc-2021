# CMakeList.txt : CMake project for AoC2021, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.12)

add_executable (day04 "main.cpp")

set_property(TARGET day04 PROPERTY CXX_STANDARD 20)

add_custom_command(
        TARGET day04 POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
                ${CMAKE_CURRENT_SOURCE_DIR}/input.txt
                ${CMAKE_CURRENT_BINARY_DIR}/day04.txt)
