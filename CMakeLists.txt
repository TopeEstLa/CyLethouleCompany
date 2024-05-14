cmake_minimum_required(VERSION 3.27)
project(CyLethouleCompany C)

set(CMAKE_C_STANDARD 11)

include_directories(
        include/
        libs/include
)


add_executable(CyLethouleCompany
        libs/include/cJSON.h
        libs/src/cJSON.c

        src/main.c
        include/world.h
        src/world.c
        include/terminal_display.h
        src/terminal_display.c
        include/maths.h
        src/maths.c
        include/world_generator.h
        src/world_generator.c
        include/file_utils.h
        src/file_utils.c
        include/saves.h
        src/saves.c
        include/entities.h
        src/entites.c
        include/terminal_ncurses_display.h
        src/terminal_ncurses_display.c
        src/printScreen.c
)

target_link_libraries(CyLethouleCompany PRIVATE
        ncurses
)