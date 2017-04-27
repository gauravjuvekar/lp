CFLAGS=-g3

macro: macro.lex.o macro.tab.o table.o macro_cb.o macro.o
	gcc $(CFLAGS) $^ -ly -ll -lm -o $@

table.o: table.c
	gcc $(CFLAGS) -c $< -o $@

macro_cb.o: macro_cb.c
	gcc $(CFLAGS) -c $< -o $@

macro.o: macro.c
	gcc $(CFLAGS) -c $< -o $@

macro.lex.o: macro.lex.c macro.tab.h
	gcc $(CFLAGS) -c $< -o $@

macro.tab.o: macro.tab.c
	gcc $(CFLAGS) -c $< -o $@

macro.lex.c: macro.l
	lex -o $@ -l $<

macro.tab.c macro.tab.h: macro.y
	yacc -o macro.tab.c --defines=macro.tab.h $<

.PHONY clean:
	rm -f *.o *.tab.c *.tab.h *.lex.c *.lex.h
