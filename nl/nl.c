#define _GNU_SOURCE 1
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>

int main(int argc, char *argv[]) {
	FILE *file;
	if (argc == 1) {
		file = stdin;
	}
	else if (argc == 2) {
		file = fopen(argv[1], "r");
		if (file == NULL) {
			fprintf(stderr, "%s\n", strerror(errno));
			exit(2);
		}
	}
	else {
		fprintf(stderr, "Usage: nl [FILE]");
		exit(1);
	}

	char *line = NULL;
	size_t size = 0;
	for(size_t line_num = 1; getline(&line, &size, file) >= 0; line_num++) {
		printf("%8zu: %s", line_num, line);
	}
	free(line);
	return 0;
}
