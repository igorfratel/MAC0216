#include "arena.h"

// typedef struct {
// 	Celula **matriz; //A arena é uma matriz de posições/celulas
// 	int x; //número de posições em cada linha da matriz
// 	int y; //número de posições em cada coluna da matriz
// 	Maquina *vetor_maq[VET_MAX] //vetor de ponteiros para máquinas virtuais com tamanho VET_MAX
// 	int robos;
// } Arena;

void cria_arena(Arena *arena, int linhas, int colunas) {
	//Recebe um número de linhas e colunas. Inicializa a arena global com essas dimensões

	int i;
	int contador_base = 0; //Indica a qual time a base gerada vai pertencer

	arena->x = linhas;
	arena->y = colunas;

  	arena->robos = 0;
 
	//Aloca as linhas da arena
	arena->matriz = (Celula**)malloc(linhas*sizeof(Celula*));

  //Para cada linhas, aloca o número especificado de colunas
  for (i = 0; i < linhas; i++) {
    arena->matriz[i] = (Celula*)malloc(colunas*sizeof(Celula));
    if (arena->matriz[i] == NULL) {
      printf("(cria_arena) Erro na alocação da matriz de celulas (2)\n");
      exit(1);
    }
  }

  //Inicializa os valores das células da matriz
  for (int i = 0; i < linhas; i++) {
    for (int j = 0; j < colunas; j++) {
      arena->matriz[i][j].terreno = -1;
      arena->matriz[i][j].equipe = -1;
      arena->matriz[i][j].cristais = 0;
      arena->matriz[i][j].ocupado = 0;
      arena->matriz[i][j].robo = NULL;
    }
  }

  if (arena->matriz == NULL) {
    printf("(cria_arena) Erro na alocação da matriz de terrenos\n");
    exit(1);
  }

	//Inicializa o vetor de bases
	for(i = 0; i < TIMES_MAX; i++)
		arena->bases[i] = NULL;

  // Inicializa os valores do vetor de bases
	//abre o arquivo terreno.txt e armazena cada linha (que é um atributo) em cada celula da matriz
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
					arena->matriz[m][n].terreno = PLANO;
					break;

				case 'F': //floresta
					arena->matriz[m][n].terreno = FLORESTA;
					break;

				case 'A': //agua
					arena->matriz[m][n].terreno = AGUA;
					break;

				case 'C': //cristal
					arena->matriz[m][n].cristais = (int)vetoratributos[k][1] - 48;
					arena->matriz[m][n].ocupado = 1;
					break;

				case 'B': //base
					arena->matriz[m][n].ocupado = 1;
					arena->matriz[m][n].terreno = BASE;
					arena->matriz[m][n].equipe = contador_base;
          			arena->bases[contador_base] = &arena->matriz[m][n];
					arena->bases[contador_base]->ocupado = 1;
					arena->bases[contador_base]->terreno = BASE;
					arena->bases[contador_base]->equipe = contador_base;
					contador_base++;
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
		arena->vetor_maq[i] = NULL;
}

void destroi_arena(Arena *arena) {
	//Libera a memória alocada para a Arena
	for (int i = 0; i < arena->y; i++)
		free(arena->matriz[i]);
	free(arena->matriz);

  for (int i = 0; i < TIMES_MAX; i++)
    arena->bases[i] = NULL;

  for (int i = 0; i < VET_MAX; i++){
    if(arena->vetor_maq[i]){
      arena->vetor_maq[i]->arena = NULL;
      destroi_pilha(arena->vetor_maq[i]->pil);
      destroi_pilha(arena->vetor_maq[i]->exec);
      free(arena->vetor_maq[i]);
    }
  }
	free(arena);
}

void mostra_arena(Arena *arena) {
	
	for(int x = 0; x < arena->x; x++) {
		for(int y = 0; y < arena->y; y++) {
		switch (arena->matriz[x][y].terreno) {
				case PLANO:
					fprintf(display, "terreno %d %d plano\n", y, x);
					break;
				case FLORESTA:
					fprintf(display, "terreno %d %d floresta\n", y, x);
					break;
				case AGUA:
					fprintf(display, "terreno %d %d rio\n", y, x);
					break;
				case BASE:
					fprintf(display, "base %d %d %d\n", arena->matriz[x][y].equipe, y, x);
					break;
			}
			if (arena->matriz[x][y].cristais) {
				fprintf(display, "cristal %d %d %d\n", arena->matriz[x][y].cristais, y, x);
			}
		}
	}
	
	for(int i = 0, j = 0; i < arena->robos; j++) {
		if(arena->vetor_maq[j] != NULL) {
			fprintf(display, "robo %d\n", arena->vetor_maq[j]->imagem);
			fprintf(display, "%d %d %d %d %d\n", i, arena->vetor_maq[j]->pos[1], arena->vetor_maq[j]->pos[0],
					arena->vetor_maq[j]->pos[1], arena->vetor_maq[j]->pos[0]);
			i++;
		}
	}
}

void escalonador(Arena *arena, int rodadas) {
	//Percorre o vetor de máquinas e manda cada uma executar NUM_INSTR instruções;
	int i;
	int j;

	for (j = 0; j < rodadas; j++){
		for (i = 0; i < arena->robos; i++){
			if(arena->vetor_maq[i] != NULL && arena->vetor_maq[i]->ocupado == 0)
				exec_maquina(arena->vetor_maq[i], NUM_INSTR);
			else if (arena->vetor_maq[i] != NULL)
				arena->vetor_maq[i]->ocupado--;
		}
	}
}

int Atualiza(Arena *arena, int equipes){
	int n_equipes = 0;
  	int equipe = -1;
	//Verifica se algum exército perdeu
	for(int i = 0; i < equipes; i++) {
		if(arena->bases[i] != NULL && arena->bases[i]->cristais == 5)
			remove_exercito(arena, arena->bases[i]->equipe);
	}

  //Verifica se algum robô morreu
	for(int i = 0, j = 0; i < VET_MAX && j < arena->robos; i++) {
		Maquina *robo = arena->vetor_maq[j];
		if(robo && robo->vida == 0) {
			arena->matriz[robo->pos[0]][robo->pos[1]].ocupado = 0;
			arena->matriz[robo->pos[0]][robo->pos[1]].robo = NULL;
  		robo = NULL;
      robo->arena = NULL;
      destroi_pilha(robo->pil);
      destroi_pilha(robo->exec);
      free(robo);
      robo = NULL;
			arena->robos--;
			j++;
		}
		else if(arena->vetor_maq[i] && equipe != robo->equipe) {
			n_equipes++;
			equipe = robo->equipe;
    }
	}
  // jogo acaba se só sobrar uma equipe
  if(n_equipes <= 1)
    return 1;
  return 0;
}

void insere_exercito(Arena *arena, int n, INSTR * p){
	static int equipe = 0;

	for(int i = arena->robos; i < n + arena->robos; i++) {
		arena->vetor_maq[i] = cria_robo(arena, equipe, p);
	}
	arena->robos += n;
	equipe++;
}

Maquina *cria_robo(Arena *arena, int equipe, INSTR * p) {
	int x, y;
	Maquina * maquina;

	srand(time(NULL));
  	x = rand() % arena->x;

	srand(time(NULL));
	y = rand() % arena->y;

	while(arena->matriz[x][y].ocupado) {
		srand(time(NULL));
	  x = rand() % arena->x;

		srand(time(NULL));
		y = rand() % arena->y;
	}
	maquina = cria_maquina(p);
  	maquina->equipe = equipe;
	maquina->arena = arena;
	maquina->pos[0] = x;
	maquina->pos[1] = y;
	arena->matriz[x][y].ocupado = 1;
    arena->matriz[x][y].robo = maquina;
	return maquina;
}

void remove_exercito(Arena *arena, int equipe){
	int i = 0, contador = 0, x, y;
	while(i < arena->robos) {
		if(arena->vetor_maq[i] != NULL && arena->vetor_maq[i]->equipe == equipe) {
			x = arena->vetor_maq[i]->pos[0];
			y = arena->vetor_maq[i]->pos[1];
			arena->matriz[x][y].ocupado = 0;
      arena->matriz[x][y].robo = NULL;
      arena->vetor_maq[i]->arena = NULL;
      destroi_pilha(arena->vetor_maq[i]->pil);
      destroi_pilha(arena->vetor_maq[i]->exec);
      free(arena->vetor_maq[i]);
      arena->vetor_maq[i] = NULL;
			contador++;
		}
		i++;
	}
	for(i = 0; i < TIMES_MAX; i++) {
		if(arena->bases[i] != NULL && arena->bases[i]->equipe == equipe) {
			arena->bases[i] = NULL;
			break;
		}
	}
	arena->robos -= contador;
}

int *busca_celula(Arena *arena, Maquina *robo, int direcao) {
	//aplicar
	//int max_i = arena->y; //linha
	//int max_j = arena->x; //coluna

	int *retorno = (int*)malloc(2 * sizeof(int));
	retorno[0] = -1;
	retorno[1] = -1;
	switch (direcao) {
	  int i, j;
		case 0:
	    	i = robo->pos[0] - 1;
	    	j = robo->pos[1];

	    	if(i >= 0) {
	      		retorno[0] = i;
	      		retorno[1] = j;
	    	}
	    	break;
		case 1:
			if (robo->pos[1] % 2 == 0){
				i = robo->pos[0];
				j = robo->pos[1] + 1;
			}

			else{
				i = robo->pos[0] - 1;
				j = robo->pos[1] + 1;
			}

			if(i >= 0 && j < 15){
				retorno[0] = i;
				retorno[1] = j;
			}
	    	break;
		case 2:
			if(robo->pos[1] % 2 == 0){
				i = robo->pos[0] + 1;
				j = robo->pos[1] + 1;
			}

			else{
				i = robo->pos[0];
				j = robo->pos[1] + 1;
			}

			if(i < 15 && j < 15){
				retorno[0] = i;
				retorno[1] = j;
			}
			break;
		case 3:
			i = robo->pos[0] + 1;
			j = robo->pos[1];

			if (i < 15){
				retorno[0] = i;
				retorno[1] = j;
			}
			break;
		case 4:
			if(robo->pos[1] % 2 == 0){
				i = robo->pos[0] + 1;
				j = robo->pos[1] - 1;
			}

			else{
				i = robo->pos[0];
				j = robo->pos[1] - 1;
			}

			if(i >= 0 && j < 15){
				retorno[0] = i;
				retorno[1] = j;
			}
			break;
		case 5:
			if(robo->pos[1] % 2 == 0){
				i = robo->pos[0];
				j = robo->pos[1] - 1;
			}

			else{
				i = robo->pos[0] - 1;
				j = robo->pos[1] - 1;
			}

			if(i >= 0 && j >= 0){
				retorno[0] = i;
				retorno[1] = j;
			}
			break;
		}
	return retorno;
}

void move(Arena *arena, Maquina * robo, int direcao) {
	int *celula = busca_celula(arena, robo, direcao);
	int posicao = -1;
	for(int i = 0; i < VET_MAX; i++){
		if(arena->vetor_maq[i] == robo){
			posicao = i;
			break;
		}
	}

	//debug
	printf("%d %d\n", robo->pos[0], robo->pos[1]);
	printf("%d %d\n", celula[0], celula[1]);
	printf("\n");

  if(posicao == -1) Erro("(move)Robô não encontrado");
	if(celula[0] != -1 && !arena->matriz[celula[0]][celula[1]].ocupado) {
		fprintf(display, "%d %d %d %d %d\n",
				posicao, robo->pos[1], robo->pos[0], celula[1], celula[0]);

		arena->matriz[celula[0]][celula[1]].ocupado = 1;
		arena->matriz[celula[0]][celula[1]].robo = robo;
		arena->matriz[robo->pos[0]][robo->pos[1]].ocupado = 0;
		arena->matriz[robo->pos[0]][robo->pos[1]].robo = NULL;
		robo->pos[1] = celula[1];
		robo->pos[0] = celula[0];

		if(arena->matriz[celula[0]][celula[1]].terreno == FLORESTA)
			robo->ocupado += 1;
		else if(arena->matriz[celula[0]][celula[1]].terreno == AGUA)
			robo->ocupado += 2;
	}
  free(celula);
}

void remove_cristal(Arena *arena, Maquina *robo, int direcao) {
	int *celula = busca_celula(arena, robo, direcao);
	if(celula[0] != -1 && arena->matriz[celula[0]][celula[1]].cristais > 0) {
		fprintf(display, "terreno %d %d plano\n",
				celula[1], celula[0]);

		robo->cristais +=arena->matriz[celula[0]][celula[1]].cristais;
		arena->matriz[celula[0]][celula[1]].cristais = 0;
	}
}

void deposita_cristal(Arena *arena, Maquina *robo, int direcao) {
	int *celula = busca_celula(arena, robo, direcao);
	if(celula[0] != -1 && arena->matriz[celula[0]][celula[1]].terreno == BASE &&
			arena->matriz[celula[0]][celula[1]].equipe != robo->equipe) {

		arena->matriz[celula[0]][celula[1]].cristais += robo->cristais;
		robo->cristais = 0;
	}
}

void ataca_robo(Arena *arena, Maquina *robo, int direcao) {
	int *posicao = busca_celula(arena, robo, direcao);
	// Se a posição não estiver na arena, não faz nada
	if(posicao[0] == -1)
		return;

	if(arena->matriz[posicao[0]][posicao[1]].ocupado &&
			arena->matriz[posicao[0]][posicao[1]].robo->equipe != robo->equipe) {
		arena->matriz[posicao[0]][posicao[1]].robo->vida -= 1;
	}
	// se o robo atacado chegar a vida 0, remove ele da arena
	if(arena->matriz[posicao[0]][posicao[1]].robo->vida == 0) {
		for(int i = 0; i < TIMES_MAX; i++) {
			if(arena->vetor_maq[i] == arena->matriz[posicao[0]][posicao[1]].robo) {
				arena->vetor_maq[i] = NULL;
				arena->matriz[posicao[0]][posicao[1]].ocupado = 0;
				break;
			}
		}
	}
}

void Sistema(Arena *arena, int op, Maquina *robo) {
	int direcao = desempilha(robo->pil).val.n;
	switch (op) {
	case 0:
		move(arena, robo, direcao);
		break;
	case 1:
		remove_cristal(arena, robo, direcao);
		break;
	case 2:
		deposita_cristal(arena, robo, direcao);
      	break;
	case 3:
		ataca_robo(arena, robo, direcao);
      	break;
	}
}
