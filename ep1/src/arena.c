#include "arena.h"

// typedef struct {
// 	Celula **matriz; //A arena é uma matriz de posições/celulas
// 	int x; //número de posições em cada linha da matriz
// 	int y; //número de posições em cada coluna da matriz
// 	Maquina *vetor_maq[VET_MAX] //vetor de ponteiros para máquinas virtuais com tamanho VET_MAX
// 	int robos;
// } Arena;

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
	int contador_base = 0; //Indica a qual time a base gerada vai pertencer

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

	//abre o arquivo terreno.txt e armazena cada linha (que eh um atributo) em cada celula da matriz
	FILE *arq;
	arq = fopen("Terreno.txt", "r");
	//vetor que guarda todos os atributos do terreno.txt
	char vetoratributos[225][10];
	if(arq == NULL)
		printf("ERRO - Nao foi possivel abrir o arquivo!\n");
	else{
		int k = 0;
		char atributo[10];
		while(fgets(atributo, sizeof atributo, arq) != NULL){
			strcpy(vetoratributos[k], atributo);
			k++;
		}
		fclose(arq);
	}

	int k = 0;
	for(int m = 0; m < linhas; m++){
		for(int n = 0; n < colunas; n++){
			switch(vetoratributos[k][0]){
				case 'P': //plano
					a->matriz[m][n].terreno = PLANO;
					break;

				case 'F': //floresta
					a->matriz[m][n].terreno = FLORESTA;
					break;

				case 'A': //agua
					a->matriz[m][n].terreno = AGUA;
					break;

				case 'C': //cristal
					a->matriz[m][n].cristais = vetoratributos[k][1];
					break;

				case 'B': //base
					a->matriz[m][n].ocupado = 1;
					a->matriz[m][n].terreno = BASE;
					a->matriz[m][n].equipe = contador_base++;
					break;
				//caso tenha um robo nesse local, nao aloca nada
				default:
					break;
			}

			k++;
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

void mostra_arena(Arena *a, FILE *display) {
	for(int x = 0; x < a->x; x++) {
		for(int y = 0; y < a->y; y++) {
			switch (a->matriz[x][y].terreno) {
				case PLANO:
					fprintf(display, "terreno %d %d plano\n", x, y);
				case FLORESTA:
					fprintf(display, "terreno %d %d floresta\n", x, y);
				case AGUA:
					fprintf(display, "terreno %d %d rio\n", x, y);
				case BASE:
					fprintf(display, "base %d %d %d\n", a->matriz[x][y].equipe, x, y);
			}
			if (a->matriz[x][y].cristais) {
				fprintf(display, "cristal %d %d %d\n", a->matriz[x][y].cristais, x, y);
			}
		}
		for(int i = 0, j = 0; i < a->robos; j++) {
			if(a->vetor_maq[j] != NULL) {
				fprintf(display, "robo %s\n", a->vetor_maq[j]->imagem);
				fprintf(display, "%d %d %d %d %d\n", i, a->vetor_maq[j]->pos[0], a->vetor_maq[j]->pos[1], 
						a->vetor_maq[j]->pos[0], a->vetor_maq[j]->pos[1]);
				i++;
			}
		}
	}
}

//$$ adicao do numero de rodadas
void escalonador(int rodadas) {
	//Percorre o vetor de máquinas e manda cada uma executar NUM_INSTR instruções;
	int i;
	int j;

	shuffle(arena.vetor_maq, VET_MAX); //shuffle a fim de embaralhar os robos, assim um equipe nao tera prioridade sobre o outro
	for (j = 0; j < rodadas; j++){
		for (i = 0; i < arena.robos; i++){
			if(arena.vetor_maq[i] != NULL)
				exec_maquina(arena.vetor_maq[i], NUM_INSTR);
		}
	}
}

void Atualiza(){
}

void insere_exercito(int n, INSTR * p){
	static int equipe = 0;

	for(int i = arena.robos; i < n + arena.robos; i++) {
		arena.vetor_maq[i] = cria_robo(equipe, p);
	}
	arena.robos += n;
	equipe++;
}

Maquina *cria_robo(int equipe, INSTR * p) {
	int x, y;
	Maquina * maquina;

	srand(time(NULL));
  x = rand() % arena.x;

	srand(time(NULL));
	y = rand() % arena.y;

	while(!arena.matriz[x][y].ocupado) {
		srand(time(NULL));
	  x = rand() % arena.x;

		srand(time(NULL));
		y = rand() % arena.y;
	}
	maquina = cria_maquina(p);
	arena.matriz[x][y].ocupado = 1;
    arena.matriz[x][y].robo = maquina;
	return maquina;

}

void remove_exercito(int equipe){
	int i, x, y;
	i = 0;
	while(i < arena.robos) {
		if(arena.vetor_maq[i] != NULL && arena.vetor_maq[i]->equipe == equipe) {
			x = arena.vetor_maq[i]->pos[0];
			y = arena.vetor_maq[i]->pos[1];
			arena.matriz[x][y].ocupado = 0;
			arena.matriz[x][y].robo = NULL;
			arena.vetor_maq[i] = NULL;
		}
		i++;
	}
}

int *busca_celula(Maquina *robo, int direcao) {
	int max_i = arena.y;
	int max_j = arena.x;
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
	      retorno[1] = j;
	      retorno[0] = i;
	    }
	    break;
	}
	return retorno;
}

void move(Maquina * robo, int direcao) {
	int *celula = busca_celula(robo, direcao);
	int posicao;
	for(int i = 0; i < VET_MAX; i++){
		if(arena->vetor_maq[i] == robo){
			posicao = i;
			break;
		}
	}

	if(celula[0] != -1 && !arena.matriz[celula[0]][celula[1]].ocupado) {
		fprintf(display, "%d %d %d %d %d\n", 
				posicao, robo->pos[0], robo->pos[1], celula[0], celula[1]);

		arena.matriz[celula[0]][celula[1]].ocupado = 1;
		arena.matriz[celula[0]][celula[1]].robo = robo;
		arena.matriz[robo->pos[0]][robo->pos[1]].ocupado = 0;
		arena.matriz[robo->pos[0]][robo->pos[1]].robo = NULL;
		robo->pos[1] = celula[1];
		robo->pos[0] = celula[0];
	}
}

void remove_cristal(Maquina *robo, int direcao) {
	int *celula = busca_celula(robo, direcao);
	if(celula[0] != -1 && arena.matriz[celula[0]][celula[1]].cristais > 0) {
		fprintf(display, "terreno %d %d plano\n",
				celula[0], celula[1]);

		robo->cristais +=arena.matriz[celula[0]][celula[1]].cristais;
		arena.matriz[celula[0]][celula[1]].cristais = 0;
	}
}

void deposita_cristal(Maquina *robo, int direcao) {
	int *celula = busca_celula(robo, direcao);
	if(celula[0] != -1 && arena.matriz[celula[0]][celula[1]].terreno == BASE && 
			arena.matriz[celula[0]][celula[1]].equipe != robo->equipe) {

		arena.matriz[celula[0]][celula[1]].cristais += robo->cristais;
		robo->cristais = 0;
	}
}

void Sistema(int op, Maquina *robo) {
  int direcao = desempilha(&robo->pil).val.n;
  switch (op) {
    case 0:
			move(robo, direcao);
			break;
		case 1:
			remove_cristal(robo, direcao);
			break;
		case 2:
			deposita_cristal(robo, direcao);
		//case 3: ataca
  }
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
