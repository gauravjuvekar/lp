
calc: calc.lex.o calc.tab.o
	gcc -ly -ll -lm $< -o $@

calc.lex.o: calc.lex.c calc.tab.h
	gcc -c $< -o $@

calc.tab.o: calc.tab.c
	gcc -c $< -o $@

calc.lex.c: calc.l
	lex -o $@ -l $<

calc.tab.c calc.tab.h: calc.y
	yacc -o calc.tab.c -d calc.tab.h $<


