/*
 * Wrap a command in an interactive shell
 * Receommend wrapping this program with rlwrap for command history other nice things
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define BUF_SIZE 512

int
main(int argc, char **argv) {
	
	if (argc < 2) {
		printf("Error: no command given\n");
		printf("Usage: %s <command> [<default> <prompt>]\n", argv[0]);
		return 1;
	}

	if (argc > 5) {
		printf("Error: too many commands given\n");
		printf("Usage: %s <command> [<default> <prompt>]\n", argv[0]);
		return 1;
	}

	char *command = argv[1];
	char *default_command;
	char *prompt_command;

	bool prompt_given = false;
	bool default_given = false;
	bool sub_command_given = false;

	char sub_command[BUF_SIZE];
	char prompt[BUF_SIZE] = "";
	char full_command[BUF_SIZE];

	if (argc >= 3) {
		default_command = argv[2];
		default_given = true;
	}
	if (argc == 4) {
		prompt_command = argv[3];
		prompt_given = true;
	}

	strcat(prompt, command);

	while (true) {
		// calculate prompt
		if (prompt_given) {
			// TODO run prompt command in subshell and capture output
		}

		// display prompt
		printf("%s> ", prompt);

		// read user input
		fgets(sub_command, BUF_SIZE, stdin);
		sub_command[strcspn(sub_command, "\n")] = 0; // remove new line
		sub_command_given = strlen(sub_command) > 1;

		// noop if no command and no default provided
		if (!default_given && !sub_command_given) {
			continue;
		}

		// build full command
		strcpy(full_command, command);
		strcat(full_command, " ");

		if (sub_command_given) {
			strcat(full_command, sub_command);
		} else {
			strcat(full_command, default_command);
		}

		// execute sub command, using default if no cmd provided
		system(full_command);
	}

	return 0;
}
