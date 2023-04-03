# Makefile TP Flex et Bison
CC = gcc
CFLAGS = -Wall
LDFLAGS = -lfl
EXEC = tpcas
SRC = ./src/
OBJ = ./obj/
BIN = ./bin/

.PHONY: clean analex

analex: $(EXEC).tab.c bin/tpcas

bin/tpcas: obj/lex.yy.o obj/$(EXEC).tab.o obj/tree.o obj/Format.o obj/symbole.o obj/ParseAsm.o
	$(CC) -o $@ $^ $(LDFLAGS)

obj/lex.yy.o: src/lex.yy.c src/$(EXEC).tab.h src/tree.h

src/lex.yy.c: src/$(EXEC).lex src/$(EXEC).tab.h src/tree.h
	flex -o src/lex.yy.c src/$(EXEC).lex

obj/Format.o: src/Format.c src/Format.h

$(OBJ)tree.o: $(SRC)tree.c $(SRC)tree.h 

$(OBJ)ParseAsm.o: $(SRC)ParseAsm.c $(SRC)ParseAsm.h

$(OBJ)symbole.o: $(SRC)symbole.c $(SRC)symbole.h 

obj/$(EXEC).tab.o: src/$(EXEC).tab.c src/$(EXEC).tab.h src/tree.h src/symbole.h

$(EXEC).tab.c: src/$(EXEC).y src/tree.h src/symbole.h
	bison -d -v src/$(EXEC).y -o src/$(EXEC).tab.c

obj/%.o: src/%.c
	$(CC) -o $@ -c $< $(CFLAGS)

clean: 
	rm -f bin/$(EXEC)
	rm -f src/$(EXEC).tab.*
	rm -f src/lex.*
	rm -f obj/*.o
	rm -f report.txt