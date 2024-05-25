#include <scene/win_menu.h>

#include <curses.h>

#include <game_controller.h>
#include <ncurses_display.h>

void win_handle_input() {
    int ch = getch();

    if (ch == ERR) return;

    if (!is_game_loaded()) {
        set_current_scene(MAIN_MENU);
        return;
    }

    switch (ch) {
        case 10:
            unload_game();
            set_current_scene(MAIN_MENU);
        default:
            break;
    }
}

void win_menu_curses() {
    printw("  ____   _    _   ____   _______                              _______  _______  ______  _____  _   _  _______\n"
           " / __ \\ | |  | | / __ \\ |__   __|    /\\                /\\    |__   __||__   __||  ____||_   _|| \\ | ||__   __|\n"
           "| |  | || |  | || |  | |   | |      /  \\    ______    /  \\      | |      | |   | |__     | |  |  \\| |   | |\n"
           "| |  | || |  | || |  | |   | |     / /\\ \\  |______|  / /\\ \\     | |      | |   |  __|    | |  | . ` |   | |\n"
           "| |__| || |__| || |__| |   | |    / ____ \\          / ____ \\    | |      | |   | |____  _| |_ | |\\  |   | |\n"
           " \\___\\_\\ \\____/  \\____/    |_|   /_/    \\_\\        /_/    \\_\\   |_|      |_|   |______||_____||_| \\_|   |_|\n"
           "\n"
           "");

    printw("\n\n");
    printw("Félicitations, la Company vient de faire un grand pas pour empêcher Morlok d'obtenir l'anneau.\n"
           "Cependant nous n'avons pas de temps, une nouvelle mission est disponible dans une autre station,\n"
           "la Company vous attend !\n\n");

    attron(A_REVERSE);
    printw("Retour au menu principal.\n");
    attroff(A_REVERSE);
}