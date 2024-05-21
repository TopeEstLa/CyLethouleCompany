#include <scene/load_menu.h>

#include <ncurses_display.h>
#include <file_utils.h>
#include <saves.h>

char **saves;
int saves_count = 0;

int current_saves = 0;

void reset_load_fields() {
    current_saves = 0;
}

void load_saves_handle_input() {
    int ch = getch();

    if (ch == ERR)
        return;

    switch (ch) {
        case KEY_UP:
            if (current_saves > 0)
                current_saves--;
            break;
        case KEY_DOWN:
            if (current_saves < saves_count)
                current_saves++;
            break;
        case 10:
            if (current_saves == saves_count) {
                set_current_scene(MAIN_MENU);
                break;
            }

            char *save = saves[current_saves];
            char* filename = get_file_path(SAVES_FOLDER, save, "");

            prepare_game();
            Game_Data *game = load_game(filename);

            if (game == NULL) {
                set_current_scene(MAIN_MENU);
                break;
            }

            loaded_game(game);
            break;
        case 27:
            set_current_scene(MAIN_MENU);
            break;
        default:
            break;
    }

}

void load_saves_menu_curses() {
    saves = list_files(SAVES_FOLDER, &saves_count);

    printw(" _             _    _                    _         _____\n"
           "| |           | |  | |                  | |       / ____|\n"
           "| |       ___ | |_ | |__    ___   _   _ | |  ___ | |       ___   _ __ ___   _ __    __ _  _ __   _   _\n"
           "| |      / _ \\| __|| '_ \\  / _ \\ | | | || | / _ \\| |      / _ \\ | '_ ` _ \\ | '_ \\  / _` || '_ \\ | | | |\n"
           "| |____ |  __/| |_ | | | || (_) || |_| || ||  __/| |____ | (_) || | | | | || |_) || (_| || | | || |_| |\n"
           "|______| \\___| \\__||_| |_| \\___/  \\__,_||_| \\___| \\_____| \\___/ |_| |_| |_|| .__/  \\__,_||_| |_| \\__, |\n"
           "                                                                           | |                    __/ |\n"
           "                                                                           |_|                   |___/\n");

    printw("\n\n");

    printw("Sélectionnez une sauvegarde\n\n");


    for (int i = 0; i < saves_count; i++) {
        char a = 'O';
        if (i == current_saves) {
            attron(A_REVERSE);
            a = 'X';
        }

        printw("[%c] %s\n", a, saves[i]);
        attroff(A_REVERSE);
    }

    printw("\n");

    char a = 'O';
    if (saves_count == current_saves) {
        attron(A_REVERSE);
        a = 'X';
    }

    printw("[%c] %s\n", a, "Retour");
    attroff(A_REVERSE);
}


