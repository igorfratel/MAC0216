#include "pilha.h"

#define MAXMEM 100

typedef struct {
  Pilha pil; //pilha de dados
  Pilha exec;
  OPERANDO Mem[MAXMEM]; //na prática, vetor de inteiros
  INSTR *prog;
  int ip;
  int rbp; //!!! registrador de base
} Maquina;

Maquina *cria_maquina(INSTR *p);

void destroi_maquina(Maquina *m);

void exec_maquina(Maquina *m, int n);
