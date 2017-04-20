%{
    #include <stdlib.h>
    #include "calc.tab.h"
    void yyerror(char *);
%}
D [0-9]
%%

({D}+|{D}*\.{D}+) {yylval.f = atof(yytext);
             return num;//return nonterminal
            }
sin  return SIN;
cos  return COS;
tan  return TAN;
log  return LOG;
sqrt return SQRT;
[ \t] ;
[-+*/=^] return *yytext;
\n       return 0;
.     ;
%%

int yywrap(void) {
    return 1;
}
