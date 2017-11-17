# compiler
  CC = gcc

# compiler flags:
  CFLAGS  = -Wall -std=gnu11

default: jogo

jogo: jogo.c types.h maq.o programas.o arena.o
	$(CC) jogo.c $(CFLAGS) -o jogo maq.o programas.o arena.o

pilha: pilha.c pilha.h
	$(CC) $(CFLAGS) -c pilha.c

arena: arena.c arena.h types.h maq.o utils.o
	$(CC) $(CFLAGS) -c arena.c

maq: maq.c maq.h
	$(CC) $(CFLAGS) -c maq.c

utils: utils.c utils.h
	$(CC) $(CFLAGS) -c utils.c

programas: programas.c programas.h types.h maq.o
	$(CC) $(CFLAGS) -c programas.c types.h maq.o

gerador: gerador_terreno.c gerador_terreno.h
	$(CC) $(CFLAGS) -c gerador_terreno.c

clean:
	$(RM) jogo *.o
