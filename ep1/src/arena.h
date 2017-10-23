#ifndef __ARENA_H__
#define __ARENA_H__

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "instr.h"
#include "maq.h"
#include "utils.h"
#define VET_MAX 100
#define NUM_INSTR 50

typedef struct Arena Arena; //Forward declaration
typedef struct Maquina Maquina; //Forward declaration

struct Arena{
	Celula **matriz; //A arena é uma matriz de celulas
	int x; //número de posições em cada linha da matriz
	int y; //número de posições em cada coluna da matriz
	Maquina *vetor_maq[VET_MAX]; //vetor de ponteiros para máquinas virtuais com tamanho VET_MAX
	int robos;
} arena;

//Recebe um número de linhas e colunas. Cria e inicializa uma Arena com essas dimensões
Arena *cria_arena(int linhas, int colunas);

//Libera a memória alocada para a Arena
void destroi_arena(Arena *a);

//Imprime a Arena linha por linha, onde cada tipo de Terreno é representado por um símbolo
void imprime_arena(Arena *a);

//Recebe uma Arena e uma máquina virtual. Salva a máquina virtual na primeira posição livre do vetor_maq da Arena.
//Retorna 1 caso seja bem sucedida e 0 caso não haja espaço para salvar a máquina virtual
int salva_maquina(Maquina *m);

//Percorre o vetor de máquinas e manda cada uma executar NUM_INSTR instruções;
void escalonador(int rodadas);

//Funcao auxiliar para criar robos e colocar na arena
Maquina *cria_robo(int time, INSTR * p);

// Funcao que insere novo exercito com n robos seguindo a instrucao p
void insere_exercito(int n, INSTR * p);

//Funcao que remove da matriz da arena e do vetor de robos da arena, os exercitos pertencentes ao time x
void remove_exercito(int time);

//Funcao que verifica se a celula para onde o robo quer se mover ou fazer qualquer outra acao esta presente na arena
//se a celula estiver na arena, retorna o vetor com os indices. Caso contrário, retorna o vetor [-1, -1]
int *checa_celula(Maquina *robo, int direcao);

// Funcao que remove os cristais de uma celula e coloca no robo
void remove_cristal(Maquina *robo, int direcao);

// Funcao que deposita os cristais do robo na celula se ela for uma base
void deposita_cristal(Maquina *robo, int direcao);

//Funcao que move o robo, caso ele possa realizar o movimento desejado
void move(Maquina * robo, int movimento);

//Funcao que troca duas posicoes de lugar
void swap(Maquina *a, Maquina *b);

//Funcao que realiza um shuffle no vetor
void shuffle(Maquina *arr[], int n);

void Sistema(int op, Maquina *m);


#endif
