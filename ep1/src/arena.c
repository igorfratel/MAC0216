#include <stdio.h>
#include <stdlib.h>
#include "arena.h"
#include "celula.h"
typedef struct {
	Celula **matriz; //A arena é uma matriz de posições/celulas
	int x; //número de posições em cada linha da matriz
	int y; //número de posições em cada coluna da matriz
	Maquina *vetor_maq[VET_MAX] //vetor de ponteiros para máquinas virtuais com tamanho VET_MAX
} Arena;

Arena *cria_arena(int linhas, int colunas) {
//Recebe um número de linhas e colunas. Cria e inicializa uma Arena com essas dimensões

	int i;

	//Aloca a struct Arena
	Arena *a = (Arena*)malloc(sizeof(Arena));
	if (a == NULL) {
		printf("(cria_arena) Erro na alocação da arena\n");
		exit(1);
	}

	a->x = colunas;
	a->y = linhas;

	//Aloca as linhas da arena
	a->matriz = (Celula**)malloc(linhas*sizeof(Celula*));
	if (a->matriz == NULL) {
		printf("(cria_arena) Erro na alocação da matriz de terrenos\n");
		exit(1);
	}

	//Para cada linhas, aloca o número especificado de colunas
	for (i = 0; i < linhas; i++) {
		a->matriz[i] = (Celula*)malloc(colunas*sizeof(Celula));
		if (a->matriz[i] == NULL) {
			printf("(cria_arena) Erro na alocação da matriz de celulas (2)\n");
			exit(1);
		}
	}

	//Inicializa todas as posições do vetor de máquinas virtuais com NULL
	for (i = 0; i < VET_MAX; i++)
		a->vetor_maq[i] = NULL;

}

void destroi_arena(Arena *a) {
//Libera a memória alocada para a Arena
	int i;

	for (i =0; i < a->y; i++)
		free(a->matriz[i]);
	free(a->matriz);
	free(a);
}

void imprime_arena(Arena *a) {
//Imprime a Arena linha por linha, onde cada tipo de celula é representado por um símbolo

}

int salva_maquina(Arena *a, *Maquina m) {
//Recebe uma Arena e uma máquina virtual. Salva a máquina virtual na primeira posição livre do vetor_maq da Arena.
//Retorna 1 caso seja bem sucedida e 0 caso não haja espaço para salvar a máquina virtual
	int i;

	for (i = 0; i < VET_MAX; i++) {
		if (a->vetor_maq[i] == NULL) {
			a->vetor_maq[i] = m;
			return 1
		}
	}
	return 0;
}

void escalonador(Arena *a) {
//Percorre o vetor de máquinas e manda cada uma executar NUM_INSTR instruções;
	int i;
	for (i = 0; i < VET_MAX; i++)
		exec_maquina(a->vetor_maq[i], NUM_INSTR);
}
