SRC := src
BIN := bin
INC := include
BUILD := build

CC := gcc
CFLAGS := -MMD -Wall -Wextra -pedantic -std=gnu17 -I$(INC)
DEBUG_FLAGS := -ggdb
RELEASE_FLAGS := -O3 -DNDEBUG

SOURCES := $(wildcard $(SRC)/*.c)
OBJ := $(patsubst $(SRC)/%.c, $(BUILD)/%.o, $(SOURCES))
DEP := $(patsubst %.o, %.d, $(OBJ))
PREFIX := ~/.local/bin

EXE := $(BIN)/repl

$(BUILD)/%.o: $(SRC)/%.c
	$(CC) $(CFLAGS) -c $^ -o $@

all: debug

debug: CFLAGS += $(DEBUG_FLAGS)
debug: build_dirs $(EXE)

$(EXE): $(OBJ)
	mkdir -p $(@D)
	$(CC) -o $@ $^ -lreadline

release: CFLAGS += $(RELEASE_FLAGS)
release: build_dirs $(EXE)

install: release
	install $(EXE) $(PREFIX)

.PHONY: build_dirs
build_dirs:
	mkdir -p bin build

.PHONY: clean
clean:
	$(RM) $(OBJ) $(DEP) $(EXE)
