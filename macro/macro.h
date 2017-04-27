#ifndef MACRO_H
#define MACRO_H 1

#include "table.h"

#include <stdbool.h>
#include <stdlib.h>
#include <ctype.h>

#define MAX_IDENTIFIER_LEN (32)
#define MAX_ARGS (16)
#define MAX_EXPANSION_DEPTH (16)


typedef struct ArgList {
	char args[MAX_ARGS][MAX_IDENTIFIER_LEN];
	size_t n_args;
} ArgList;

typedef struct MacroDeclaration {
	char name[MAX_IDENTIFIER_LEN];
	ArgList arglist;
} MacroDeclaration;

typedef struct InputLine {
	char label[MAX_IDENTIFIER_LEN];
	char mnemonic[MAX_IDENTIFIER_LEN];
	ArgList arglist;
} InputLine;

typedef struct MacroTableEntry {
	MacroDeclaration declaration;
	size_t entries_start;
	size_t entries_end;
} MacroTableEntry;

extern Table defined_macros;
extern Table macro_contents;

void init_macro_tables(void);

int macro_lookup_input_line(const void *search, const void *table_term);
int macro_lookup_declaration(const void *search, const void *table_term);
void emit_output_line(const InputLine *line);
int find_arg_in_arglist(const char *arg, const ArgList *arglist);


#endif /* ifndef ASM_H */
