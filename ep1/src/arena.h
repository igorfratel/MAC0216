#ifndef __ARENA_H__
#define __ARENA_H__

#include <stdio.h>
#include <stdlib.h>
#include "maq.h"
#include "terreno.h"
#include "utils.h"
#define VET_MAX 100
#define NUM_INSTR 50

typedef struct {
	Celula **matriz; //A arena é uma matriz de celulas
	int x; //número de posições em cada linha da matriz
	int y; //número de posições em cada coluna da matriz
	Maquina *vetor_maq[VET_MAX] //vetor de ponteiros para máquinas virtuais com tamanho VET_MAX
	int robos;
} Arena;

//Recebe um número de linhas e colunas. Cria e inicializa uma Arena com essas dimensões
Arena *cria_arena(int linhas, int colunas);

//Libera a memória alocada para a Arena
void destroi_arena(Arena *a);

//Imprime a Arena linha por linha, onde cada tipo de Terreno é representado por um símbolo
void imprime_arena(Arena *a);

//Recebe uma Arena e uma máquina virtual. Salva a máquina virtual na primeira posição livre do vetor_maq da Arena.
//Retorna 1 caso seja bem sucedida e 0 caso não haja espaço para salvar a máquina virtual
int salva_maquina(Arena *a, *Maquina m);

//Percorre o vetor de máquinas e manda cada uma executar NUM_INSTR instruções;
void escalonador(Arena *a);

//Funcao auxiliar para criar robos e colocar na arena
Maquina *cria_robo(Arena * arena, int time, INSTR * p);

//Funcao que remove da matriz da arena e do vetor de robos da arena, os exercitos pertencentes ao time x
void remove_exercito(Arena * arena, int time);

//Funcao que move o robo, caso ele possa realizar o movimento desejado
int move(Arena * arena, Maquina * robo, int movimento);
#endif
