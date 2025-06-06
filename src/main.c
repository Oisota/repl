/*
 * Wrap a program that uses subcommands in an interactive shell
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <getopt.h>
#include "util.h"

#define NAME "REPL"
#define VERSION "0.1.0"

int
main(int argc, char **argv) {

	void capture_command_output(char*, char*);

	char *base_command = argv[1];
	char *default_command;
	char *prompt_command;
	char *sub_command;

	bool default_given = false;
	bool prompt_given = false;
	bool sub_command_given = false;

	char prompt[BUF_SIZE] = "";
	char full_command[BUF_SIZE] = "";
	

	// parse and validate cli args
	if (argc < 2) {
		fprintf(stderr, "Error: no command given\n");
		fprintf(stderr, "Usage: %s <command> [<default> <prompt>]\n", argv[0]);
		return 1;
	}

	if (argc > 5) {
		fprintf(stderr, "Error: too many commands given\n");
		fprintf(stderr, "Usage: %s <command> [<default> <prompt>]\n", argv[0]);
		return 1;
	}

	if (argc >= 3) {
		default_command = argv[2];
		default_given = true;
	}

	if (argc == 4) {
		prompt_command = argv[3];
		prompt_given = true;
	}

	while (true) {
		// calculate prompt
		if (prompt_given) {
			capture_command_output(prompt_command, prompt);
			strcat(prompt, " ");
		}
		strcat(prompt, base_command);
		strcat(prompt, "> ");

		// display prompt, read user input
		sub_command = readline(prompt);
		memset(prompt, 0, BUF_SIZE); // reset prompt buffer

		if (sub_command == NULL) { // exit if we hit EOF (ctrl-d)
			break;
		}

		sub_command_given = strlen(sub_command) > 1;

		if (sub_command_given) {
			add_history(sub_command);
		}

		// noop if no command and no default provided
		if (!default_given && !sub_command_given) {
			continue;
		}

		// build full command
		strcpy(full_command, base_command);
		strcat(full_command, " ");

		if (sub_command_given) {
			strcat(full_command, sub_command);
		} else {
			strcat(full_command, default_command);
		}

		// execute sub command, using default if no cmd provided
		system(full_command);
		free(sub_command);
	}

	return 0;
}
