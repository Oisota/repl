#ifndef OPTS_H
#define OPTS_H

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

struct ParsedOptions* parse_cli_args(int argc, char **argv);
void free_opts(struct ParsedOptions*);

#endif
