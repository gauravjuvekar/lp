%{
#include <stdlib.h>
#include <string.h>
#include "macro.h"
#include "macro.tab.h"
%}

IDENTIFIER [0-9a-zA-Z][0-9a-zA-Z_]*
%%
MACRO {
	return MACRO_START;
}
MEND {
	return MACRO_END;
}
END {
	return END;
}
&{IDENTIFIER} {
	strcpy(yylval.identifier, yytext);
	return MACRO_ARG;
}
{IDENTIFIER} {
	strcpy(yylval.identifier, yytext);
	return IDENTIFIER;
}
[ \t] ;
[:,\n] {
	return *yytext;
}
%%
