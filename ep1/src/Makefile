# compiler
  CC = gcc

# compiler flags:
  CFLAGS  = -Wall

default: motor

motor: motor.c pilha.o maq.o
	$(CC) motor.c $(CFLAGS) -o motor pilha.o maq.o 

pilha:
	$(CC) $(CFLAGS) -c pilha

maq:
	$(CC) $(CFLAGS) -c maq

clean:
	$(RM) motor *.o