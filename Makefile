CC = gcc

CFLAGS = -std=c11 -Ilibs/include -Iinclude -Iinclude/scene

LIBS = -lncursesw

SRC = libs/src/cJSON.c \
	src/main.c src/world.c src/world_generator.c src/entities.c src/memory_utils.c src/maths.c src/file_utils.c src/saves.c src/terminal_display.c \
	src/ncurses_display.c src/player.c src/monsters.c src/items.c src/game_controller.c src/shop.c src/fight.c \
	src/scene/create_menu.c src/scene/fight_menu.c src/scene/fight_shop.c src/scene/game_over_menu.c src/scene/game_scene.c \
	src/scene/load_menu.c src/scene/main_menu.c src/scene/pause_menu.c src/scene/shop_menu.c src/scene/time_over_menu.c \
	src/scene/tutorial_menu.c src/scene/win_menu.c

OBJ = $(SRC:.c=.o)

TARGET = CyLethouleCompany

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^ $(LIBS)

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -f $(OBJ) $(TARGET)