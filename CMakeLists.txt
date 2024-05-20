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
        include/scene/main_menu.h
        src/scene/main_menu.c
        include/scene/load_menu.h
        src/scene/load_menu.c
        include/scene/create_menu.h
        src/scene/create_menu.c
        include/player.h
        src/player.c
        include/game_controller.h
        src/game_controller.c
        include/scene/game_scene.h
        src/scene/game_scene.c
        include/scene/pause_menu.h
        src/scene/pause_menu.c
        include/memory_utils.h
        src/memory_utils.c
        include/monsters.h
        src/monsters.c
        include/items.h
        src/items.c
        include/scene/time_over_menu.h
        src/scene/time_over_menu.c
        include/scene/game_over_menu.h
        src/scene/game_over_menu.c
)

target_link_libraries(CyLethouleCompany PRIVATE
        ncursesw
)