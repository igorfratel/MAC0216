# compiler
CC = gcc

# compiler flags:
CFLAGS  = -Wall -std=gnu11

default: jogo gerador

jogo: jogo.c acertos.o symrec.o compila.tab.o lex.yy.o types.h utils.o pilha.o maq.o programas.o arena.o
	$(CC) jogo.c $(CFLAGS) -lfl -o jogo types.h utils.o pilha.o maq.o acertos.o symrec.o compila.tab.o lex.yy.o programas.o arena.o

utils: utils.c utils.h
	$(CC) $(CFLAGS) -c utils.c

pilha: pilha.c pilha.h
	$(CC) $(CFLAGS) -c pilha.c

maq: maq.c maq.h arena.o pilha.o utils.o types.o
		$(CC) $(CFLAGS) -c maq.c arena.o pilha.o utils.o types.o

arena: arena.c arena.h types.h maq.o utils.o
	$(CC) $(CFLAGS) -c arena.c

compila.tab.o: compila.y
	bison -d compila.y
	gcc -c compila.tab.c

lex.yy.o: compila.l
	flex compila.l
	gcc -c lex.yy.c

programas: programas.c programas.h compila.tab.o compila.tab.h lex.yy.o types.h maq.o
	$(CC) $(CFLAGS) -c programas.c

#compila: compila.tab.o lex.yy.o symrec.o acertos.o maq.o pilha.o motor.o utils.o arena.o
	#gcc -o $@ $^ -lm -lfl
acertos: acertos.c acertos.h
	$(CC) $(CFLAGS) -c acertos.c

symrec: symrec.c symrec.h
	$(CC) $(CFLAGS) -c symrec.c


gerador: gerador_terreno.c
	$(CC) $(CFLAGS) gerador_terreno.c -o gerador_terreno


clean:
	rm -f *.o jogo lex.yy.c compila.tab.c compila.tab.h *~ compila
