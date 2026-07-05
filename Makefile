CC = gcc
CFLAGS = -Wall -Wextra -Werror -g -Iinclude
LDFLAGS = -lm
SOURCES = src/main.c src/livre.c src/bibliotheque.c src/membres.c src/utilitaire.c src/menu.c
OBJECTS = $(SOURCES:.c=.o)
EXECUTABLE = start

# Portable remove command: use cmd /C del on Windows, rm on Unix
ifeq ($(OS),Windows_NT)
RM = cmd /C del /F /Q
EXE = .exe
else
RM = rm -f
EXE =
endif

# Files to remove for clean (use backslashes on Windows)
CLEAN_FILES = $(OBJECTS) $(EXECUTABLE)$(EXE)
ifeq ($(OS),Windows_NT)
CLEAN_FILES := $(subst /,\\,$(CLEAN_FILES))
endif

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

run: $(EXECUTABLE)
	./$(EXECUTABLE)

clean:
	-@$(RM) $(CLEAN_FILES)

.PHONY: all clean run
