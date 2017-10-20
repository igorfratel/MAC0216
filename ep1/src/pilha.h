#ifndef __PILHA_H__
#define __PILHA_H__

#include <stdio.h>
#include <stdlib.h>
#include "instr.h"
#include "utils.h"

#define PILMAX 99

typedef struct {
  int topo;
  OPERANDO val[PILMAX+1];
} Pilha;

Pilha *cria_pilha();
void destroi_pilha(Pilha *p);
void empilha(Pilha *p, OPERANDO op);
OPERANDO desempilha(Pilha *p);
void imprime(Pilha *p, int n);

#endif
