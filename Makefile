CC = gcc
CFLAGS = -std=c11 -Wall -Wextra -I./vendor/include -L./vendor/lib -lSDL2_ttf -lSDL2 -Wl,-subsystem,windows -DSDL_MAIN_HANDLED
SRCS = main.c graphics.c alien.c  # Ajoutez les fichiers ici
OBJS = $(SRCS:.c=.o)

alien_simulation: $(OBJS)
	$(CC) -o $@ $^ $(CFLAGS)

%.o: %.c
	$(CC) -c $< $(CFLAGS)

clean:
	rm -f alien_simulation $(OBJS)