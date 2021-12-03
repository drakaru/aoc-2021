cmake_minimum_required (VERSION 3.12)

add_executable (day03 "main.cpp")

set_property(TARGET day03 PROPERTY CXX_STANDARD 20)

add_custom_command(
        TARGET day03 POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
                ${CMAKE_CURRENT_SOURCE_DIR}/input.txt
                ${CMAKE_CURRENT_BINARY_DIR}/day03.txt)
