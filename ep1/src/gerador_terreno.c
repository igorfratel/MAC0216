#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

/*
	Exercitos (B1 B2 B3 B4 B5)
	-Minimo: 2
	-Maximo: 5

	Numero de robos em cada exercito (B1.1, B1.2, B1.3...)
	-Minimo: 1
	-Maximo: 5

	-criar repositorios de cristais
	-distribuir as bases
	-distribuir os terrenos

	Terreno:
	-Plano (1 timestep para se mover) (P)
	-Rugoso (2 timesteps para se mover) (R)
	-Esburacado (3 timesteps para se mover) (E)

	Cristais
	-Repositorios com 1, 2 ou 3 cristais (C1 C2 C3)
	-Minimo de cristais no jogo: numero de exercitos * 5
	-Maximo = 2 * minimo
	-Nota: temos que ter um numero minimo de cristais para o jogo nao dar empate

	Se um exercito for eliminado, a sua base torna-se um repositorio de cristais que estavam com esse exercito
	Numero maximo de cristais por exercito: 5

	Cada exercito deve coletar 5 cristais, apos isso, deve procurar uma base inimiga

	dar um shuffle no vetor set!

	TAMANHO DO TERRENO:
	-P/ 2 exercitos (numero max de robos: 10): numero de robos * 20
	-P/ 3 exercitos (numero max de robos: 15):
	-P/ 4 exercitos (numero max de robos: 20): 
		...

	RESUMO DE ATRIBUTOS
	-TERRENO
	PLANO (P)
	RUGOSO (R)
	ESBURACADO (E)

	BASES (B1, B2, B3..)
	ROBOS (R1.1, R2.4, R5.3..)
	CRISTAIS (C1, C2, C3)
*/

int main(){

	int exercitos;
	int robos;

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

	int contador_1 = 1;
	//pode ser modificado posteriormente
	int tamanho_arena = exercitos * robos * 20;
	char conjunto_atributos[tamanho_arena][50]; 
	//exercitos
	while(contador_1 <= exercitos){
		
		char aux_1[2] = "B";
		char aux_2[2];

		sprintf(aux_2, "%d", contador_1);
		strcat(aux_1, aux_2);

		strcpy(conjunto_atributos[contador_1], aux_1);
		contador_1++;
	}

	//robos
	int contador_2 = 1;
	int contador_3 = 1;
	while(contador_2 <= exercitos){
		while(contador_3 <= robos){

			char aux_1[4] = "R";
			char aux_2[4];
			char aux_3[4];
			char aux_4[4] = ".";

			sprintf(aux_2, "%d", contador_2);
			strcat(aux_1, aux_2);

			sprintf(aux_3, "%d", contador_3);
			strcat(aux_1, aux_4);
			strcat(aux_1, aux_3);

			strcpy(conjunto_atributos[contador_1], aux_1);

			contador_1++;
			contador_3++;
		}

		contador_2++;
		contador_3 = 1;
	}

	int cristais = exercitos * 8;
	int contador = 0;

    time_t t;
    srand((unsigned) time(&t));
    int min = 1;
    int max = 3;

    //cristais
	while (contador < cristais){
		char aux_1[] = "C";
		int aleatorio_i = rand() % (max + 1 - min) + min;
		char aleatorio_c[4];
		sprintf(aleatorio_c, "%d", aleatorio_i);
		strcat(aux_1, aleatorio_c);

		strcpy(conjunto_atributos[contador_1], aux_1);
		contador_1++;
		contador++;
	}

	//terreno
	while(contador_1 < tamanho_arena){
		int aleatorio_i = rand() % (max + 1 - min) + min;
		
		if (aleatorio_i == 1){
			strcpy(conjunto_atributos[contador_1], "P");
		}

		if (aleatorio_i == 2){
			strcpy(conjunto_atributos[contador_1], "R");
		}

		if (aleatorio_i == 3){
			strcpy(conjunto_atributos[contador_1], "E");
		}

		contador_1++;
	}


	//shuffle no vetor!
	int numeros[tamanho_arena];
	int contador_4 = 1;

	while(contador_4 < tamanho_arena){
		numeros[contador_4] = contador_4;
		contador_4++;
	}

	void swap(int *a, int *b) {
    	int temp = *a;
    	*a = *b;
    	*b = temp;
	}

	void randomize(int arr[], int n) {
    	srand(time(NULL));
    	int i;
    	for(i = n - 1; i > 0; i--) {
        	int j = rand() % (i + 1);
        	swap(&arr[i], &arr[j]);
    	}
	}

	randomize (numeros, tamanho_arena);

/*
	int contador_teste = 0;
	while(contador_teste < tamanho_arena){
		printf("%d\n", numeros[contador_teste]);
		contador_teste++;
	}
*/

	char vetor_shuffle[tamanho_arena][50];
	int contador_5 = 1;
	while(contador_5 < tamanho_arena){
		int numero = numeros[contador_5];
		strcpy(vetor_shuffle[contador_5], conjunto_atributos[numero]);
		printf("%s\n", vetor_shuffle[contador_5]);
		contador_5++;
	}

/*
	//teste
	int teste = 1;
	while(teste < tamanho_arena - 1){
		printf("%s\n", vetor_shuffle[teste]);
		teste++;
	}
*/
}