#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <assert.h>

#include "table.h"
#include "macro.h"
#include "macro_cb.h"

typedef enum State {
	STATE_DEFINING,
	STATE_NORMAL_PROCESSING,
	STATE_EXPANDING,
} State;

State g_state = STATE_NORMAL_PROCESSING;
int g_currently_defining = -1;

void subst_args(
		ArgList *input,
		ArgList *call,
		ArgList *declaration) {
	assert(input->n_args == call->n_args &&
			call->n_args == declaration->n_args);
	for (size_t input_i = 0; input_i < input->n_args; input_i++) {
		if (input->args[input_i][0] == '&') {
			int replace_i = find_arg_in_arglist(
					input->args[input_i],
					declaration);
			if (replace_i >= 0) {
				strcpy(input->args[input_i], call->args[replace_i]);
			}
			else {
				/* Undeclared arg, ignore for now */
			}
		}
	}
}

void expand_macro(InputLine *line, MacroTableEntry *entry, int recursion_left) {
	if (!recursion_left) {
		fprintf(stderr, "*** Max recursion depth while expanding\n");
		assert(0);
	}
	for (int line_i = entry->entries_start;
			line_i < (int)entry->entries_end; line_i++) {
		InputLine macro_line = *((InputLine *)
				table_get(&macro_contents, line_i));
		subst_args(
				&(macro_line.arglist),
				&(line->arglist),
				&(entry->declaration.arglist));
		int index;
		if ((index = table_index(
						&defined_macros,
						&macro_line,
						macro_lookup_input_line)) >= 0) {
			/* Nested call */
			expand_macro(
					&macro_line,
					table_get(&defined_macros, index),
					recursion_left - 1);
		}
		else {
			emit_output_line(&macro_line);
		}
	}
}

void cb_macro_declaration(MacroDeclaration declaration) {
	if (g_state != STATE_NORMAL_PROCESSING) {
		fprintf(
				stderr,
				"*** Declaration while expanding or defining %s(%d)\n",
				declaration.name, (int)declaration.arglist.n_args);
		assert(0);

	}
	int index = table_index(
			&defined_macros,
			&declaration,
			macro_lookup_declaration);
	if (index < 0) {
		MacroTableEntry entry;
		entry.declaration = declaration;
		entry.entries_start = macro_contents.n_entries;
		g_currently_defining = table_insert(&defined_macros, &entry);
		assert(g_currently_defining >= 0);
		g_state = STATE_DEFINING;
	}
	else {
		fprintf(
				stderr,
				"*** Re-declaration of %s(%d)\n",
				declaration.name, (int)declaration.arglist.n_args);
		assert(0);
	}
}

void cb_end_input(void) {
	if (g_state != STATE_NORMAL_PROCESSING) {
		assert(g_state == STATE_DEFINING);
		fprintf(stderr, "*** Unexpected EOF while defining a macro\n");
		assert(0);
	}
}


void cb_macro_end(void) {
	if (g_state != STATE_DEFINING) {
		fprintf(stderr, "*** Misplaced MEND\n");
		assert(0);
	}
	MacroTableEntry *entry = table_get(&defined_macros, g_currently_defining);
	entry->entries_end = macro_contents.n_entries;
	g_currently_defining = -1;
	g_state = STATE_NORMAL_PROCESSING;
}

void cb_asm_line(InputLine line) {
	assert(g_state != STATE_EXPANDING);
	if (g_state == STATE_NORMAL_PROCESSING) {
		int index;
		if ((index = table_index(
						&defined_macros,
						&line,
						macro_lookup_input_line)) >= 0) {
			MacroTableEntry *entry = table_get(&defined_macros, index);
			g_state = STATE_EXPANDING;
			expand_macro(&line, entry, MAX_EXPANSION_DEPTH);
			g_state = STATE_NORMAL_PROCESSING;
		}
		else {
			emit_output_line(&line);
		}
	}
	else {
		assert(g_state == STATE_DEFINING);
		table_insert(&macro_contents, &line);
	}
}
