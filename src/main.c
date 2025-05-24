#include <stdio.h>

int
main(int argc, char **argv) {
	
	if (argc == 0) {
		printf("Error: no command given");
		printf("Usage: repl <command> (<default> <prompt>)");
	}

	printf("REPL!");

	return 0;
}
