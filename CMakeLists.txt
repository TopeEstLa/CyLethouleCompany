cmake_minimum_required(VERSION 3.27)
project(CyLethouleCompany C)

set(CMAKE_C_STANDARD 11)

include_directories(
        include/
)

add_executable(CyLethouleCompany src/main.c
        include/world.h
        src/world.c
        include/terminal_display.h
        src/terminal_display.c
        include/math.h
        src/math.c
)
