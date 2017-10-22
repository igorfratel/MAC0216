#include "arena.h"

// typedef struct {
// 	Celula **matriz; //A arena é uma matriz de posições/celulas
// 	int x; //número de posições em cada linha da matriz
// 	int y; //número de posições em cada coluna da matriz
// 	Maquina *vetor_maq[VET_MAX] //vetor de ponteiros para máquinas virtuais com tamanho VET_MAX
// 	int robos;
// } Arena;

//shuffle no vetor
void swap(Maquina *a, Maquina *b) {
    Maquina temp = *a;
    *a = *b;
    *b = temp;
}

void shuffle(Maquina *arr[], int n) {
    srand(time(NULL));
    int i;
    for(i = n - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        swap(arr[i], arr[j]);
    }
}

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
	return a;
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

int salva_maquina(Arena *a, Maquina *m) {
//Recebe uma Arena e uma máquina virtual. Salva a máquina virtual na primeira posição livre do vetor_maq da Arena.
//Retorna 1 caso seja bem sucedida e 0 caso não haja espaço para salvar a máquina virtual
	int i;

	for (i = 0; i < VET_MAX; i++) {
		if (a->vetor_maq[i] == NULL) {
			a->vetor_maq[i] = m;
			return 1;
		}
	}
	return 0;
}


//$$ adicao do numero de rodadas
void escalonador(Arena *a, int rodadas) {
//Percorre o vetor de máquinas e manda cada uma executar NUM_INSTR instruções;
	int i;
	int j;

	shuffle(a->vetor_maq, VET_MAX); //shuffle a fim de embaralhar os robos, assim um equipe nao tera prioridade sobre o outro
	for (j = 0; j < rodadas; j++){
		for (i = 0; i < a -> robos; i++){
			if(a->vetor_maq[i] != NULL)
				exec_maquina(a->vetor_maq[i], NUM_INSTR);
		}
	}
}

void Atualiza(){
}

void insere_exercito(Arena * arena, int n, INSTR * p){
	static int equipe = 0;

	for(int i = arena->robos; i < n + arena->robos; i++) {
		arena->vetor_maq[i] = cria_robo(arena, equipe, p);
	}
	arena->robos += n;
	equipe++;
}

Maquina *cria_robo(Arena * arena, int equipe, INSTR * p) {
	int x, y;
	Maquina * maquina;

	srand(time(NULL));
  x = rand() % arena->x;

	srand(time(NULL));
	y = rand() % arena->y;

	while(!arena -> matriz[x][y].ocupado) {
		srand(time(NULL));
	  x = rand() % arena->x;

		srand(time(NULL));
		y = rand() % arena->y;
	}
	maquina = cria_maquina(p);
	arena->matriz[x][y].ocupado = 1;
	return maquina;

}

void remove_exercito(Arena * arena, int equipe){
	int i, x, y;
	i = 0;
	while(i < arena->robos) {
		if(arena->vetor_maq[i] != NULL && arena->vetor_maq[i]->equipe == equipe) {
			x = arena->vetor_maq[i]->pos[0];
			y = arena->vetor_maq[i]->pos[1];
			arena->matriz[x][y].ocupado = 0;
			arena->vetor_maq[i] = NULL;
		}
		i++;
	}
}

int *checa_celula(Arena *arena, Maquina *robo, int direcao) {
	int max_i = arena->y;
	int max_j = arena->x;
	int *retorno = (int*)malloc(2 * sizeof(int*));
	retorno[0] = -1;
	retorno[1] = -1;
	switch (direcao) {
	  int i, j;

	  case 0:
	    i = robo->pos[0] - 1;
	    j = robo->pos[1];
	    if(i >= 0) {
	      retorno[1] = j;
	      retorno[0] = i;
	    }
	    break;
	  case 1:
	    j = robo->pos[1] + 1;

	    if(robo->pos[0] % 2 != 0)
	      i = robo->pos[0] - 1;
	    else
	      i = robo->pos[0];

	    if(i >= 0 && j < max_j) {
	      retorno[1] = j;
	      retorno[0] = i;
	    }
	    break;
	  case 2:
	    j = robo->pos[1] + 1;

	    if(robo->pos[0] % 2 != 0)
	      i = robo->pos[0];
	    else
	      i = robo->pos[0] + 1;

	    if(i < max_i && j < max_j) {
	      retorno[1] = j;
	      retorno[0] = i;
	    }
	    break;
	  case 3:
	    i = robo->pos[0] + 1;
	    j = robo->pos[1];
	    if(i < max_i) {
	      retorno[1] = j;
	      retorno[0] = i;
	    }
	    break;
	  case 4:
	    j = robo->pos[1] - 1;

	    if(robo->pos[0] % 2 != 0)
	      i = robo->pos[0];
	    else
	      i = robo->pos[0] + 1;

	    if(i < max_i && j >= 0) {
	      retorno[1] = j;
	      retorno[0] = i;
	    }
	    break;
	  case 5:
	    j = robo->pos[1] - 1;

	    if(robo->pos[0] % 2 != 0)
	      i = robo->pos[0] - 1;
	    else
	      i = robo->pos[0];

	    if(i >= 0 && j >= 0) {
	      arena->matriz[i][j].ocupado = 1;
	      retorno[1] = j;
	      retorno[0] = i;
	    }
	    break;
	}
	return retorno;
}

int move(Arena * arena, Maquina * robo, int direcao) {
	int *celula = checa_celula(arena, robo, direcao);
	if(celula[0] != -1 && !arena->matriz[celula[0]][celula[1]].ocupado) {
		arena->matriz[celula[0]][celula[1]].ocupado = 1;
		robo->pos[1] = celula[1];
		robo->pos[0] = celula[0];
	}
	return;
}

int remove_cristal(Arena *arena, Maquina *robo, int direcao) {
	int *celula = checa_celula(arena, robo, direcao);
	if(celula[0] != -1 && arena->matriz[celula[0]][celula[1]].cristais > 0) {
		robo->cristais +=arena->matriz[celula[0]][celula[1]].cristais;
		arena->matriz[celula[0]][celula[1]].cristais = 0;
	}
	return;
}

int deposita_cristal(Arena *arena, Maquina *robo, int direcao) {
	int *celula = checa_celula(arena, robo, direcao);
	if(celula[0] != -1 && arena->matriz[celula[0]][celula[1]].terreno == BASE) {
		arena->matriz[celula[0]][celula[1]].cristais += robo->cristais;
		robo->cristais = 0;
	}
	return;
}
void Sistema(int op, Maquina *m) {
	return;
}

// void remove_exercito(Arena * arena, int equipe){
// 	int i, max, x, y;
// 	i = 0;
// 	max = arena->robos;
// 	int removeu = 0;
// 	while(i < max && removeu == 0) {
// 		while(arena->vetor_maq[i] != NULL && arena->vetor_maq[i].equipe == equipe) {
// 			x = arena->vetor_maq[i].pos[0];
// 			y = arena->vetor_maq[i].pos[1];
// 			arena->matriz[x][y].ocupado = 0;
// 			arena->vetor_maq[i] = NULL;
// 			removeu = 1;
// 			i++;
// 		}
// 		i++;
// 	}
// }
