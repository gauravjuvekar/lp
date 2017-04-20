%{
       #include<stdio.h>
       #include<math.h>
       #include<stdlib.h>
       int yylex(void);
       void yyerror(char *s);
%}

%union { float f;}
%token<f> num
%token SIN COS TAN LOG SQRT

/*Defining the Precedence and Associativity*/

%left '+' '-'   //lowest precedence
%left '*' '/'
%nonassoc '^'   //highest precedenc
%nonassoc uminu //no associativity
%type<f> exp    //Sets the type for non - terminal

%%

/* for storing the answer */
ss: exp {printf("=%g\n",$1);}

/* for binary arithmatic operators */
exp :  exp '+' exp { $$ = $1 + $3; }
      |exp '-' exp { $$ = $1 - $3; }
      |exp '*' exp { $$ = $1 * $3; }
      |exp '/' exp {if($3 == 0) {
                       printf("Divide By Zero");
                       exit(0);
                    }
                    else {
                        $$ = $1 / $3;
                    }
                   }
      |exp '^' exp { $$ = powf($1, $3); }
      |'-' exp     { $$ = -$2; }
      |'(' exp ')' {$$ = $2; }
      |SIN '(' exp ')' { $$ = sin($3); }
      |COS '(' exp ')' { $$ = cos($3); }
      |TAN '(' exp ')' { $$ = tan($3); }
      |LOG '(' exp ')' { $$ = log($3); }
      |SQRT '(' exp ')' { $$ = sqrt($3); }
      |num
      ;
%%

int main() {
    while (1) {
        yyparse();
    }
}

void yyerror(char *s) {
    fprintf(stderr, "%s\n", s);
}

