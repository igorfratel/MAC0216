#ifndef __TERRENO_H__
#define __TERRENO_H__

typedef struct {
	int tipo; //Estrada, montanha, rio, etc
	int cristais; //Número de cristais presente
	int ocupado; //1 se está ocupado por um robô; 0 c.c
	int base; //Indica se é uma base e de qual exército
} Terreno;

#endif