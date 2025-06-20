#ifndef UTIL_H
#define UTIL_H

#include <stdbool.h>

#define BUF_SIZE 512
#define NAME "REPL"
#define VERSION "0.1.3"

struct CommandOption {
	char *text;
	bool present;
};

struct ParsedOptions {
	struct CommandOption *base_command;
	struct CommandOption *default_command;
	struct CommandOption *prompt_command;
};

struct ParsedOptions* parse_cli_args();
void capture_command_output(char*, char*);
void free_opts(struct ParsedOptions*);

#endif
