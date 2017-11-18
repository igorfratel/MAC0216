# compiler
  CC = gcc

# compiler flags:
  CFLAGS  = -Wall -std=gnu11 -g -O -Wextra

default: jogo gerador

jogo: jogo.c types.h utils.o pilha.o maq.o programas.o arena.o
	$(CC) jogo.c $(CFLAGS) -o jogo types.h utils.o pilha.o maq.o programas.o arena.o

utils: utils.c utils.h
	$(CC) $(CFLAGS) -c utils.c

pilha: pilha.c pilha.h
	$(CC) $(CFLAGS) -c pilha.c

maq: maq.c maq.h arena.o pilha.o utils.o types.o
		$(CC) $(CFLAGS) -c maq.c arena.o pilha.o utils.o types.o

arena: arena.c arena.h types.h maq.o utils.o
	$(CC) $(CFLAGS) -c arena.c

programas: programas.c programas.h types.h maq.o
	$(CC) $(CFLAGS) -c programas.c types.h maq.o

gerador: gerador_terreno.c
	$(CC) $(CFLAGS) gerador_terreno.c -o gerador_terreno

clean:
	$(RM) jogo gerador_terreno *.o
