CC = gcc
CFLAGS = -Wall -Wextra -Werror -g -Iinclude
LDFLAGS = -lm
SOURCES = src/main.c src/livre.c src/bibliotheque.c src/membres.c src/utilitaire.c src/menu.c
OBJECTS = $(SOURCES:.c=.o)
EXECUTABLE = start

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

run: $(EXECUTABLE)
	./$(EXECUTABLE)

clean:
	-del /F /Q src\*.o 2>nul
	-del /F /Q $(EXECUTABLE).exe 2>nul
	-del /F /Q $(EXECUTABLE) 2>nul

.PHONY: all clean run
