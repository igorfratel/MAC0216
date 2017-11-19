#include "arena.h"
#include "programas.h"

extern FILE *display;
int main() {

	int exercitos;
	int robos;

	INSTR *p0;
	INSTR *p1;
	INSTR *p2;
	INSTR *p3;
	INSTR *p4;

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
			p0 = devolve_programa(0);
			p1 = devolve_programa(1);
			insere_exercito(minha_arena, robos, p0);
			insere_exercito(minha_arena, robos, p1);
			break;

		case 3:
			p0 = devolve_programa(0);
			p1 = devolve_programa(1);
			p2 = devolve_programa(2);
			insere_exercito(minha_arena, robos, p0);
			insere_exercito(minha_arena, robos, p1);
			insere_exercito(minha_arena, robos, p2);
			break;

		case 4:
			p0 = devolve_programa(0);
			p1 = devolve_programa(1);
			p2 = devolve_programa(2);
			p3 = devolve_programa(3);
			insere_exercito(minha_arena, robos, p0);
			insere_exercito(minha_arena, robos, p1);
			insere_exercito(minha_arena, robos, p2);
			insere_exercito(minha_arena, robos, p3);
			break;

		case 5:
			p0 = devolve_programa(0);
			p1 = devolve_programa(1);
			p2 = devolve_programa(2);
			p3 = devolve_programa(3);
			p4 = devolve_programa(4);
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
}
