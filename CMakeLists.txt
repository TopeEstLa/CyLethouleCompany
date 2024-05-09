cmake_minimum_required(VERSION 3.27)
project(CyLethouleCompany C)

set(CMAKE_C_STANDARD 11)

include_directories(
        include/
        deps/include/cJSON
)

link_directories(
        deps/libs
)

add_executable(CyLethouleCompany src/main.c
        include/world.h
        src/world.c
        include/terminal_display.h
        src/terminal_display.c
        include/math.h
        src/math.c
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
)

target_link_libraries(CyLethouleCompany PRIVATE
        cjson
        ncurses
)