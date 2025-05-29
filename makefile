CC := gcc
CFLAGS := -MMD -Wall -Wextra -pedantic -std=gnu17
DEBUG_FLAGS := -ggdb

SRC := $(wildcard src/*.c)
OBJ := $(SRC:%.c=%.o)
DEP := $(OBJ:%.o=%.d)
BUILD := build

EXE := $(BUILD)/repl

all: debug

debug: CFLAGS += $(DEBUG_FLAGS)
debug: $(EXE)

$(EXE): $(OBJ)
	$(CC) -o $@ $^

.PHONY: clean
clean:
	$(RM) $(OBJ) $(DEP) $(EXE)
