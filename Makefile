CC = gcc
CFLAGS = -Wall -Wextra -std=c11 -Iinclude
LDFLAGS = -lncurses
SRC = $(wildcard src/*.c)
OBJ = $(SRC:src/%.c=build/objects/%.o)
BIN = build/axonTE

all: $(BIN)

build/objects/%.o: src/%.c
	@mkdir -p build/objects
	$(CC) $(CFLAGS) -c $< -o $@

$(BIN): $(OBJ)
	$(CC) $(OBJ) -o $(BIN) $(LDFLAGS)

clean:
	rm -rf build

install: $(BIN)
	sudo cp $(BIN) /usr/local/bin/axonTE
	sudo chmod +x /usr/local/bin/axonTE

uninstall:
	sudo rm -f /usr/local/bin/axonTE

make_install: $(BIN) install

.PHONY: all clean install uninstall make_install

