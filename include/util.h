#ifndef UTIL_H
#define UTIL_H

#include <stdbool.h>

#define BUF_SIZE 512

struct CommandOption {
	char *text;
	bool present;
};

void capture_command_output(char*, char*);

#endif
