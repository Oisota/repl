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

all: debug

debug: CFLAGS += $(DEBUG_FLAGS)
debug: $(EXE)

$(EXE): $(OBJ)
	mkdir -p $(@D)
	$(CC) -o $@ $^ -lreadline

release: CFLAGS += $(RELEASE_FLAGS)
release: $(EXE)

install: release
	install $(EXE) $(PREFIX)

.PHONY: clean
clean:
	$(RM) $(OBJ) $(DEP) $(EXE)
