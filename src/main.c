/*
 * Wrap a program that uses subcommands in an interactive shell
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "util.h"

int
main(int argc, char **argv) {

	char prompt[BUF_SIZE] = "";
	char full_command[BUF_SIZE] = "";
	struct CommandOption sub_command;
	struct ParsedOptions *opts = parse_cli_args(argc, argv);

	while (true) {
		// calculate prompt
		if (opts->prompt_command->present) {
			capture_command_output(opts->prompt_command->text, prompt);
			strcat(prompt, " ");
		}
		strcat(prompt, opts->base_command->text);
		strcat(prompt, "> ");

		// display prompt, read user input
		sub_command.text = readline(prompt);
		memset(prompt, 0, BUF_SIZE); // reset prompt buffer

		if (sub_command.text == NULL) { // exit if we hit EOF (ctrl-d)
			break;
		}

		sub_command.present = strlen(sub_command.text) > 1;

		if (sub_command.present) {
			add_history(sub_command.text);
		}

		// noop if no command and no default provided
		if (!opts->default_command->present && !sub_command.present) {
			continue;
		}

		// build full command
		strcpy(full_command, opts->base_command->text);
		strcat(full_command, " ");

		if (sub_command.present) {
			strcat(full_command, sub_command.text);
		} else {
			strcat(full_command, opts->default_command->text);
		}

		// execute sub command, using default if no cmd provided
		system(full_command);
		free(sub_command.text);
	}
	free(opts);

	return 0;
}
