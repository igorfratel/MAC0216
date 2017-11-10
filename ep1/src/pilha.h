#ifndef __PILHA_H__
#define __PILHA_H__

#include <stdio.h>
#include <stdlib.h>
#include "types.h"
#include "utils.h"

Pilha *cria_pilha();
void destroi_pilha(Pilha *p);
void empilha(Pilha *p, OPERANDO op);
OPERANDO desempilha(Pilha *p);
void imprime(Pilha *p, int n);

#endif
