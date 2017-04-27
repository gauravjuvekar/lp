#define _POSIX_C_SOURCE 1
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "macro.h"
#include "table.h"

Table defined_macros;
Table macro_contents;

void init_macro_tables(void) {
	table_init(&defined_macros, sizeof(MacroTableEntry));
	table_init(&macro_contents, sizeof(InputLine));
}

int macro_lookup_input_line(const void *search, const void *table_term) {
	InputLine *input_line = (InputLine *)search;
	MacroTableEntry *entry = (MacroTableEntry *) table_term;
	return !(input_line->arglist.n_args == entry->declaration.arglist.n_args &&
			 !strcmp(input_line->mnemonic, entry->declaration.name));
}

int macro_lookup_declaration(const void *search, const void *table_term) {
	MacroDeclaration *declaration = (MacroDeclaration *)search;
	MacroTableEntry *entry = (MacroTableEntry *) table_term;
	return !(declaration->arglist.n_args == entry->declaration.arglist.n_args &&
			 !strcmp(declaration->name, entry->declaration.name));
}

void emit_output_line(const InputLine *line) {
	if (line->label[0] != '\0') {
		printf("%s: ", line->label);
	}
	printf("%s", line->mnemonic);
	if (line->arglist.n_args) {
		printf(" %s", line->arglist.args[0]);
	}
	for (size_t i = 1; i < line->arglist.n_args; i++) {
		printf(", %s", line->arglist.args[i]);
	}
	printf("\n");
}

int find_arg_in_arglist(const char *arg, const ArgList *arglist) {
	for (size_t i = 0; i < arglist->n_args; i++) {
		if (!strcmp(arg, arglist->args[i])) {
			return i;
		}
	}
	return -1;
}
