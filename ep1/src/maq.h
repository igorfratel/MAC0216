#ifndef __MAQ_H__
#define __MAQ_H__

#include "pilha.h"

#define MAXMEM 100
typedef struct {
  //@@
  int pos[2];
  int cristais;

  Pilha pil;
  Pilha exec;
  OPERANDO Mem[MAXMEM];
  INSTR *prog;
  OPERANDO rbp; //!!!
  OPERANDO ip;
} Maquina;

Maquina *cria_maquina(INSTR *p);

void destroi_maquina(Maquina *m);

void exec_maquina(Maquina *m, int n);

#endif
