#include "motor.h"
#include "motor2.h"
#include "arena.h"
int main() {
	Arena *minha_arena = cria_arena(3, 3);
	INSTR *p = devolve_programa();
	INSTR *p2 = devolve_programa();
	insere_exercito(1, p);
	printf("oi\n");
	insere_exercito(1, p2);
	escalonador(1);

	destroi_arena(minha_arena);


}