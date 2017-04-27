%{
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "macro.h"
#include "macro_cb.h"

int yylex(void);
void yyerror(char *s);
%}

%union {
    MacroDeclaration declaration;
    InputLine input_line;
    ArgList arg_list;
    char identifier[MAX_IDENTIFIER_LEN];
}
%token <identifier> IDENTIFIER MACRO_ARG
%token MACRO_START MACRO_END END
%type <declaration> declaration
%type <input_line> asm_line line_start
%type <arg_list> macro_arglist call_arglist
%type <identifier> arg label
%%
input: /* empty */
    |   input line
    ;
line:
        '\n'
    |   declaration '\n' {
            cb_macro_declaration($1);
        }
    |   END '\n' {
            cb_end_input();
        }
    |   MACRO_END '\n' {
            cb_macro_end();
        }
    |   asm_line '\n' {
            cb_asm_line($1);
        }
    ;
declaration:
        MACRO_START IDENTIFIER macro_arglist {
            MacroDeclaration tmp;
            strcpy(tmp.name, $2);
            memcpy(&(tmp.arglist), &($3), sizeof(tmp.arglist));
            $$ = tmp;
        }
    ;
macro_arglist:
        MACRO_ARG {
			ArgList tmp;
			tmp.n_args = 1;
			strcpy(tmp.args[0], $1);
			$$ = tmp;
        }
	|   macro_arglist ',' MACRO_ARG {
			strcpy(($1).args[($1).n_args], $3);
			($1).n_args += 1;
			$$ = $1;
		}
    ;
arg:
        IDENTIFIER {
			strcpy($$, $1);
		}
    |   MACRO_ARG {
			strcpy($$, $1);
		}
    ;
call_arglist:
        arg {
			ArgList tmp;
			tmp.n_args = 1;
			strcpy(tmp.args[0], $1);
			$$ = tmp;
        }
    |   call_arglist ',' arg {
			strcpy(($1).args[($1).n_args], $3);
			($1).n_args += 1;
			$$ = $1;
		}
    ;
label:
        IDENTIFIER ':' {
			strcpy($$, $1);
		}
    ;
line_start:
		IDENTIFIER {
			InputLine tmp;
			strcpy(tmp.mnemonic, $1);
			tmp.label[0] = '\0';
			$$ = tmp;
		}
    |   label IDENTIFIER {
			InputLine tmp;
			strcpy(tmp.mnemonic, $2);
			strcpy(tmp.label, $1);
			$$ = tmp;
		}
    ;
asm_line:
		line_start macro_arglist
    |   line_start call_arglist {
			($1).arglist = $2;
			$$ = $1;
		}
    ;
%%
int main() {
	yyparse();
}
