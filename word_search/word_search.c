#define _GNU_SOURCE 1
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>

int main(int argc, char *argv[]) {
	FILE *file;
	if (argc == 2) {
		file = stdin;
	}
	else if (argc == 3) {
		file = fopen(argv[2], "r");
		if (file == NULL) {
			fprintf(stderr, "%s\n", strerror(errno));
			exit(2);
		}
	}
	else {
		fprintf(stderr, "Usage: nl word [FILE]");
		exit(1);
	}

	const char *search_string = argv[1];

	char *line = NULL;
	size_t size = 0;
	for(size_t line_num = 1; getline(&line, &size, file) >= 0; line_num++) {
		char *word = line - 1;
		while((word = strstr(word + 1, search_string)) != NULL) {
			printf("%zu:%zu\n", line_num, word - line + 1);
		}
	}
	free(line);
	return 0;
}
