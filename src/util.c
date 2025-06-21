#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>
#include "util.h"

/*
 * Parse cli args into data struct
 */
struct ParsedOptions*
parse_cli_args(int argc, char **argv) {
	void print_usage(const char*);
	struct ParsedOptions *opts = malloc(sizeof(struct ParsedOptions));
	struct CommandOption *base_command = malloc(sizeof(struct CommandOption));
	struct CommandOption *default_command = malloc(sizeof(struct CommandOption));
	struct CommandOption *prompt_command = malloc(sizeof(struct CommandOption));
	opts->base_command = base_command;
	opts->default_command = default_command;
	opts->prompt_command = prompt_command;

	static struct option long_options[] = {
		{"help", no_argument, NULL, 'h'},
		{"version", no_argument, NULL, 'v'},
		{"default", required_argument, NULL, 'd'},
		{"prompt", required_argument, NULL, 'p'},
		{NULL, 0, NULL, 0}
	};
	const char *short_opts = "hvd:p:";
	int c;
	int option_index = 0;
	opterr = 0;

	if (argc == 1) {
		print_usage(argv[0]);
	}

	while ((c = getopt_long(argc, argv, short_opts, long_options, &option_index)) != -1) {
		switch (c) {
			case 'h':
				printf("Usage: %s [options] <command>\n", argv[0]);
				printf("Wrap a command that takes sub-commands in an interactive repl shell\n");
				printf("Example:\n");
				printf("  $ repl --default status git\n  git>\n\n");
				printf("  $ repl --default ps docker\n  docker>\n\n");
				printf("Options:\n");
				printf("  -h, --help              Display this information\n");
				printf("  -v, --version           Display program version information\n");
				printf("  -d, --default <command> Set the default command\n");
				printf("  -p, --prompt <command>  Set the command to run in order to calculate the repl prompt.\n");
				printf("                          This will prefix the built in prompt with the result of execution.\n");
				printf("                          The prompt is recalculated on input from the user.\n\n");
				printf("<command> The final non option argument is the command to wrap in the repl\n");
				exit(0);

			case 'v':
				printf("%s %s\n", NAME, VERSION);
				exit(0);

			case 'd':
				default_command->text = optarg;
				default_command->present = true;
				break;

			case 'p':
				prompt_command->text = optarg;
				prompt_command->present = true;
				break;

			case '?':
				print_usage(argv[0]);
				break;

			default:
				print_usage(argv[0]);
		}
	}

	if (optind < argc) {
		base_command->text = argv[optind++];
	}

	return opts;

}

void
print_usage(const char* prog) {
	fprintf(stderr, "Usage: %s [options] <command>\n", prog);
	fprintf(stderr, "Run %s --help for more info.\n", prog);
	exit(1);
}

/*
 * Capture the output of the shell command (cmd) and write it to dst
 */
void
capture_command_output(char* cmd, char* dst) {
	FILE *fp;
	char tmp[BUF_SIZE];

	fp = popen(cmd, "r");
	if (NULL == fp) {
		printf("Failed to run command: %s\n", cmd);
	}

	while(fgets(tmp, BUF_SIZE, fp) != NULL) {
		tmp[strcspn(tmp, "\n")] = 0; // remove new line
		strcat(dst, tmp);
	}

	int status = pclose(fp);
	if (status == -1) {
		printf("Error closing pipe\n");
	}
}

void
free_opts(struct ParsedOptions *opts) {
	free(opts->base_command);
	free(opts->default_command);
	free(opts->prompt_command);
	free(opts);
}
