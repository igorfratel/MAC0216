#ifndef __MAQ_H__
#define __MAQ_H__

#include <stdio.h>
#include <stdlib.h>
#include "arena.h"
#include "pilha.h"
#include "utils.h"
#include "types.h"

Arena arena;

Maquina *cria_maquina(INSTR *p);

void destroi_maquina(Maquina *m);

void exec_maquina(Maquina *m, int n);

int new_frame(Maquina *m, int pos);

int del_frame(Maquina *m);

#endif
