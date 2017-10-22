# compiler
  CC = gcc

# compiler flags:
  CFLAGS  = -Wall -std=c11

default: motor

motor: motor.c utils.o pilha.o maq.o arena.o 
	$(CC) motor.c $(CFLAGS) -o motor pilha.o arena.o maq.o utils.o 

pilha: pilha.c pilha.h
	$(CC) $(CFLAGS) -c pilha

arena: arena.c arena.h
	$(CC) $(CFLAGS) -c maq

maq: maq.c maq.h
	$(CC) $(CFLAGS) -c maq

utils: utils.c utils.h
	$(CC) $(CFLAGS) -c utils

clean:
	$(RM) motor *.o