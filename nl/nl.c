#define _GNU_SOURCE 1
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char *argv[]) {
	(void) argc;
	(void) argv;

	char *line = NULL;
	size_t size = 0;
	for(size_t line_num = 1; getline(&line, &size, stdin) >= 0; line_num++) {
		printf("%8zu: %s", line_num, line);
	}
	free(line);
	return 0;
}
