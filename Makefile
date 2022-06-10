SRC= $(wildcard *.c)
OBJ= $(SRC:.c=.o)
CFLAGS=-Wall
DEBUG=-O0 -g -fsanitize=address -fno-omit-frame-pointer
LDFLAGS=-lncurses $(CFLAGS)

all: CFLAGS += -O3
all: LDFLAGS += -O3
all: gol

debug: CFLAGS += $(DEBUG)
debug: LDFLAGS += $(DEBUG)
debug: gol

gol: $(OBJ)
	@$(CC) -o $@ $^ $(LDFLAGS)

%.o: %.c
	@$(CC) -o $@ -c $< $(CFLAGS)

clean:
	@rm -f *.o
	@rm -f gol
