#include "arena.h"
int main() {
	Arena *minha_arena
	cria_arena(minha_arena, 15, 15);
	while(1){
		// INSTR *p = devolve_programa();
		// INSTR *p2 = devolve_programa();
		// insere_exercito(1, p);

		// insere_exercito(1, p2);
		escalonador(NUM_INSTR);
		Atualiza(minha_arena, 5);
		//
		mostra_arena();
	}
	destroi_arena(minha_arena);
}
