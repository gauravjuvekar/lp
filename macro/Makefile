
macro: macro.lex.o macro.tab.o table.o macro_cb.o
	gcc $^ -ly -ll -lm -o $@

table.o: table.c
	gcc -c $< -o $@

macro_cb.o: macro_cb.c
	gcc -c $< -o $@

macro.lex.o: macro.lex.c macro.tab.h
	gcc -c $< -o $@

macro.tab.o: macro.tab.c
	gcc -c $< -o $@

macro.lex.c: macro.l
	lex -o $@ -l $<

macro.tab.c macro.tab.h: macro.y
	yacc -o macro.tab.c --defines=macro.tab.h $<


