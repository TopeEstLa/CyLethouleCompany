#include <scene/pause_menu.h>

#include <ncurses_display.h>

#include <curses.h>
#include <string.h>

#include <saves.h>
#include <file_utils.h>

char *pause_options[] = {
        "Reprendre la partie",
        "Sauvegarder la partie",
        "Retourner au menu principal",
};
int pause_count = 3;

int pause_choice = 0;
struct timeval pause_start;

int calc_pause_time(struct timeval start, struct timeval end) {
    long seconds = end.tv_sec - start.tv_sec;
    long useconds = end.tv_usec - start.tv_usec;

    if (useconds < 0) {
        seconds -= 1;
        useconds += 1000000;
    }

    return seconds;
}


void reset_pause_fields() {
    pause_choice = 0;
    gettimeofday(&pause_start, NULL);
}

void pause_handle_input() {
    int ch = getch();

    if (ch == ERR)
        return;

    if (!is_game_loaded()) return;
    Game_Data *game_data = get_game_data();

    struct timeval end;
    gettimeofday(&end, NULL);

    int duration = calc_pause_time(pause_start, end);

    switch (ch) {
        case 27:
            game_data->end_time.tv_sec += duration;
            set_current_scene(GAME);
            break;
        case KEY_UP:
            if (pause_choice > 0)
                pause_choice--;
            break;
        case KEY_DOWN:
            if (pause_choice < pause_count - 1)
                pause_choice++;
            break;
        case 10:
            switch (pause_choice) {
                case 0:
                    game_data->end_time.tv_sec += duration;
                    set_current_scene(GAME);
                    break;
                case 1:
                    gettimeofday(&pause_start, NULL);
                    game_data->end_time.tv_sec += duration;
                    char *filename = get_file_path(SAVES_FOLDER, get_game_data()->player->name, ".sav");
                    save_game(get_game_data(), filename);
                    break;
                case 2:
                    //unload game
                    unload_game();
                    set_current_scene(MAIN_MENU);
                    break;
                default:
                    break;
            }
            break;
        default:
            break;
    }
}

void pause_menu_curses() {
    printw(" _____             _    _   _____  ______\n"
           "|  __ \\     /\\    | |  | | / ____||  ____|\n"
           "| |__) |   /  \\   | |  | || (___  | |__\n"
           "|  ___/   / /\\ \\  | |  | | \\___ \\ |  __|\n"
           "| |      / ____ \\ | |__| | ____) || |____\n"
           "|_|     /_/    \\_\\ \\____/ |_____/ |______|\n"
           "\n"
           "");

    printw("\n\n");

    for (int i = 0; i < pause_count; i++) {
        char a = 'O';
        if (i == pause_choice) {
            attron(A_REVERSE);
            a = 'X';
        }

        printw("[%c] %s\n", a, pause_options[i]);
        attroff(A_REVERSE);
    }
}
