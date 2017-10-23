#ifndef __MAQ_H__
#define __MAQ_H__

#include <stdio.h>
#include <stdlib.h>
#include "arena.h"
#include "pilha.h"
#include "utils.h"

#define MAXMEM 100

typedef struct Arena Arena; //Forward declaration
typedef struct Maquina Maquina; //Forward declaration

struct Maquina {
  //@@
  int equipe;
  int pos[2];
  int cristais;
  Arena *arena;

  Pilha pil;
  Pilha exec;
  OPERANDO Mem[MAXMEM];
  INSTR *prog;
  OPERANDO rbp; //!!!
  OPERANDO ip;
};

Maquina *cria_maquina(INSTR *p);

void destroi_maquina(Maquina *m);

void exec_maquina(Maquina *m, int n);

#endif
