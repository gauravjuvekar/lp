#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "table.h"
#include "macro.h"
#include "macro_cb.h"

void cb_macro_declaration(MacroDeclaration declaration) {
	printf("Got a declaration\n");
	printf("%s", declaration.name);
}
void cb_end_input(void) {
	printf("End of input\n");
}
void cb_macro_end(void) {
	printf("End of macro definition\n");
}
void cb_asm_line(InputLine line) {
	printf("Got an asm line\n");
	printf("%s: %s ...\n", line.label, line.mnemonic);
}
