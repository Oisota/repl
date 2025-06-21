#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "util.h"
#include "opts.h"

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
