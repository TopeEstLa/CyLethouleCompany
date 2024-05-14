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
        include/ncurses_display.h
        src/ncurses_display.c
        include/scene/main_menu_scene.h
        src/scene/main_menu_scene.c
        include/scene/load_menu_scene.h
        src/scene/load_menu_scene.c
        include/frame_rate.h
        src/frame_rate.c
)

target_link_libraries(CyLethouleCompany PRIVATE
        ncurses
)