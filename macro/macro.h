#ifndef MACRO_H
#define MACRO_H 1

#include "table.h"

#include <stdbool.h>
#include <stdlib.h>
#include <ctype.h>

#define MAX_IDENTIFIER_LEN (32)
#define MAX_ARGS (16)


typedef struct ArgList {
	char args[MAX_ARGS][MAX_IDENTIFIER_LEN];
	size_t n_args;
} ArgList;

typedef struct MacroDeclaration {
	char name[MAX_IDENTIFIER_LEN];
	ArgList arglist;
} MacroDeclaration;

typedef enum InputLineType {
	INPUT_LINE_NORMAL,
	INPUT_LINE_MACRO_DECLARATION,
	INPUT_LINE_MEND,
	INPUT_LINE_END,
	INPUT_LINE_BLANK
} InputLineType;

typedef struct InputLine {
	InputLineType type;
	char label[MAX_IDENTIFIER_LEN];
	char mnemonic[MAX_IDENTIFIER_LEN];
	ArgList arglist;
} InputLine;

typedef struct MacroTableEntry {
	MacroDeclaration declaration;
	size_t entries_start;
	size_t entries_end;
} MacroTableEntry;

extern const Table defined_macros;
extern const Table macro_contents;

int instruction_table_lookup_mnemonic(const void *search,
                                      const void *table_term);
int operand_table_lookup_mnemonic(const void *search, const void *table_term);


#endif /* ifndef ASM_H */
