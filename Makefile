CC = gcc
CFLAGS = -Wall -Wextra -Werror -g -Iinclude
LDFLAGS = -lm
SOURCES = src/main.c src/livre.c src/bibliotheque.c src/membres.c
OBJECTS = $(SOURCES:.c=.o)
EXECUTABLE = start
all: $(EXECUTABLE)
$(EXECUTABLE): $(OBJECTS)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@
clean:
	rm -f $(OBJECTS) $(EXECUTABLE)
.PHONY: all clean
