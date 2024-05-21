CC = gcc

CFLAGS =

LIBS = -lncursesw

SRC =

OBJ = $(SRC:.c=.o)

TARGET = CyLethouleCompany

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^ $(LIBS)

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -f $(OBJ) $(TARGET)