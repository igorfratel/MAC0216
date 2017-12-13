#include "arena.h"
#include "programas.h"
#include "gerador_terreno.h"
#include <time.h>

extern FILE *display;
int main() {

	int exercitos;
	int robos;

	INSTR *p0 = malloc(2000*sizeof(INSTR));
	INSTR *p1 = malloc(2000*sizeof(INSTR));
	INSTR *p2 = malloc(2000*sizeof(INSTR));
	INSTR *p3 = malloc(2000*sizeof(INSTR));
	INSTR *p4 = malloc(2000*sizeof(INSTR));

	//numero de exercitos (bases)
	printf("Insira o numero de exercitos (Minimo 2, maximo 5): ");
	scanf("%d", &exercitos);
	while (exercitos < 2 || exercitos > 5){
		printf("Insira o numero de exercitos (Minimo 2, maximo 5): ");
		scanf("%d", &exercitos);
	}

	//numero de robos
	printf("Insira o numero de robos em cada exercito (Minimo 1, maximo 5): ");
	scanf("%d", &robos);
	while(robos < 1 || robos > 5){
		printf("Insira o numero de robos em cada exercito (Minimo 1, maximo 5): ");
		scanf("%d", &robos);
	}

	int fim = 0;
	display = popen("./display_game.py", "w");
	Arena *minha_arena = (Arena*)malloc(sizeof(Arena));
	cria_arena(minha_arena, 15, 15);

	switch(exercitos){
		case 2:
			devolve_programa(0, p0);
			devolve_programa(1, p1);
			insere_exercito(minha_arena, robos, p0);
			insere_exercito(minha_arena, robos, p1);
			break;

		case 3:
			devolve_programa(0, p0);
			devolve_programa(1, p1);
			devolve_programa(2, p2);
			insere_exercito(minha_arena, robos, p0);
			insere_exercito(minha_arena, robos, p1);
			insere_exercito(minha_arena, robos, p2);
			break;

		case 4:
			devolve_programa(0, p0);
			devolve_programa(1, p1);
			devolve_programa(2, p2);
			devolve_programa(3, p3);
			insere_exercito(minha_arena, robos, p0);
			insere_exercito(minha_arena, robos, p1);
			insere_exercito(minha_arena, robos, p2);
			insere_exercito(minha_arena, robos, p3);
			break;

		case 5:
			devolve_programa(0, p0);
			devolve_programa(1, p1);
			devolve_programa(2, p2);
			devolve_programa(3, p3);
			devolve_programa(4, p4);
			insere_exercito(minha_arena, robos, p0);
			insere_exercito(minha_arena, robos, p1);
			insere_exercito(minha_arena, robos, p2);
			insere_exercito(minha_arena, robos, p3);
			insere_exercito(minha_arena, robos, p4);
			break;

	}

	mostra_arena(minha_arena);
	while(!fim){
		escalonador(minha_arena, NUM_INSTR);
		fim = Atualiza(minha_arena, exercitos);
	}
	destroi_arena(minha_arena);
	free(p0);
	free(p1);
	free(p2);
	free(p3);
	free(p4);
}
