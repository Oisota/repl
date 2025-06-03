CC := gcc
CFLAGS := -MMD -Wall -Wextra -pedantic -std=gnu17
DEBUG_FLAGS := -ggdb
RELEASE_FLAGS := -O3 -DNDEBUG

SRC := $(wildcard src/*.c)
OBJ := $(SRC:%.c=%.o)
DEP := $(OBJ:%.o=%.d)
BUILD := build
PREFIX := ~/.local/bin

EXE := $(BUILD)/repl

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
