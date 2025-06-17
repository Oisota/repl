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

extern int opterr;

int
main(int argc, char **argv) {

	void capture_command_output(char*, char*);

	struct CommandOption base_command, default_command, prompt_command, sub_command;
	char prompt[BUF_SIZE] = "";
	char full_command[BUF_SIZE] = "";
	int c;

	static struct option long_options[] = {
		{"help", no_argument, NULL, 'h'},
		{"version", no_argument, NULL, 'v'},
		{"default", required_argument, NULL, 'd'},
		{"prompt", required_argument, NULL, 'p'},
		{NULL, 0, NULL, 0}
	};
	const char *short_opts = "hvd:p:";
	int option_index = 0;
	opterr = 0;

	while ((c = getopt_long(argc, argv, short_opts, long_options, &option_index)) != -1) {
		switch (c) {
			case 'h':
				printf("Usage: %s [options] <command>\n", argv[0]);
				printf("Wrap a command that takes sub-commands in an interactive repl shell\n");
				printf("Example: repl --default status git\n\n");
				printf("Options:\n");
				printf("  -h, --help              Display this information\n");
				printf("  -v, --version           Display program version information\n");
				printf("  -d, --default <command> Set the default command\n");
				printf("  -p, --prompt <command>  Set the command to run in order to calculate the repl prompt\n\n");
				printf("<command> The final non option argument is the command to wrap in the repl\n");
				exit(0);

			case 'v':
				printf("%s %s\n", NAME, VERSION);
				exit(0);

			case 'd':
				default_command.text = optarg;
				default_command.present = true;
				break;

			case 'p':
				prompt_command.text = optarg;
				prompt_command.present = true;
				break;

			case '?':
				fprintf(stderr, "Usage: %s [options] <command>\n", argv[0]);
				exit(1);

			default:
				fprintf(stderr, "Usage: %s [options] <command>\n", argv[0]);
				exit(1);
		}
	}

	if (optind < argc) {
		base_command.text = argv[optind++];
	}


	while (true) {
		// calculate prompt
		if (prompt_command.present) {
			capture_command_output(prompt_command.text, prompt);
			strcat(prompt, " ");
		}
		strcat(prompt, base_command.text);
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
		if (!default_command.present && !sub_command.present) {
			continue;
		}

		// build full command
		strcpy(full_command, base_command.text);
		strcat(full_command, " ");

		if (sub_command.present) {
			strcat(full_command, sub_command.text);
		} else {
			strcat(full_command, default_command.text);
		}

		// execute sub command, using default if no cmd provided
		system(full_command);
		free(sub_command.text);
	}

	return 0;
}
