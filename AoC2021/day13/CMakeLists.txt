cmake_minimum_required (VERSION 3.12)

add_executable (day13 "main.cpp")

set_property(TARGET day13 PROPERTY CXX_STANDARD 20)

add_custom_command(
        TARGET day13 POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
                ${CMAKE_CURRENT_SOURCE_DIR}/input.txt
                ${CMAKE_CURRENT_BINARY_DIR}/day13.txt)
