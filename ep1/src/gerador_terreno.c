#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
//Programa que gera os atributos que a arena precisa ter ao ser inicializada, definindo assim o
//tipo de terreno, quantidade de repositorios e numero de cristais em cada um, bases dos exercitos,
//localizacao dos robos

//compilando e executando:
//gcc gerador_terreno.c
//./a.out

/*
	UMA PRE DEFINICAO DAS REGRAS E ELEMENTOS DO JOGO, QUE PODEM SER ALTERADAS NA PROXIMA FASE
	APENAS A CRITERIO DE ORGANIZACAO E ENTENDIMENTO DO JOGO

	Exercitos (B1 B2 B3 B4 B5)
	-Minimo: 2
	-Maximo: 5

	Numero de robos em cada exercito (R1.1, R1.2, R1.3...)
	-Minimo: 1
	-Maximo: 5

	Terreno:
	-Plano (1 timestep para se mover) (P)
	-Floresta (2 timesteps para se mover) (F)
	-Agua (3 timesteps para se mover) (A)

	Cristais
	-Repositorios com 1, 2 ou 3 cristais (C1 C2 C3)
	-Minimo de cristais no jogo: numero de exercitos * 5
	-Maximo = 2 * minimo
	-Nota: temos que ter um numero minimo de cristais para o jogo nao dar empate

	Se um exercito for eliminado, a sua base torna-se um repositorio de cristais que estavam com esse exercito
	Numero maximo de cristais por exercito: 5

	Cada exercito deve coletar 5 cristais, apos isso, deve procurar uma base inimiga

	TAMANHO DO TERRENO:
	-P/ 2 exercitos (numero max de robos: 10): numero de robos * 20
	-P/ 3 exercitos (numero max de robos: 15):
	-P/ 4 exercitos (numero max de robos: 20): 
		...

	RESUMO DE ATRIBUTOS
	-TERRENO
	PLANO (P)
	FLORESTA (F)
	AGUA (A)

	BASES (B1, B2, B3..)
	ROBOS (R1.1, R2.4, R5.3..)
	CRISTAIS (C1, C2, C3)
*/

//funcao que copia strings 
char *copiastr(char *dest, char *orig)
{
    int i;

    for(i = 0 ; i < strlen(orig) ; i++){
        dest[i] = orig[i];
    }

    dest[i] = '\0';
    return dest;
}

//funcoes swap e randomize para o shuffle do vetor
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
	//int tamanho_arena = exercitos * robos * 20;
	int tamanho_arena = 15 * 15; //alteracao (10/11/2017)
	char conjunto_atributos[tamanho_arena + 1][8]; 

	//exercitos
	while(contador_1 <= exercitos){
		char aux_1[8] = "B";
		char aux_2[8];
		sprintf(aux_2, "%d", contador_1);
		strcat(aux_1, aux_2);
		copiastr(conjunto_atributos[contador_1], aux_1);
		contador_1++;
	}

	//robos
	
	int contador_2 = 1;
	int contador_3 = 1;
	while(contador_2 <= exercitos){
		while(contador_3 <= robos){
			char aux_1[8] = "VAZIO";
			//char aux_2[8];
			//char aux_3[8];
			//char aux_4[8] = ".";
			//sprintf(aux_2, "%d", contador_2);
			//strcat(aux_1, aux_2);
			//sprintf(aux_3, "%d", contador_3);
			//strcat(aux_1, aux_4);
			//strcat(aux_1, aux_3);
			copiastr(conjunto_atributos[contador_1], aux_1);

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
		char aleatorio_c[8];
		sprintf(aleatorio_c, "%d", aleatorio_i);
		strcat(aux_1, aleatorio_c);
		copiastr(conjunto_atributos[contador_1], aux_1);
		contador_1++;
		contador++;
	}

	//terreno
	while(contador_1 < tamanho_arena + 1){
		int aleatorio_i = rand() % (max + 1 - min) + min;
		
		//plano
		if (aleatorio_i == 1){
			copiastr(conjunto_atributos[contador_1], "P");
		}

		//floresta
		if (aleatorio_i == 2){
			copiastr(conjunto_atributos[contador_1], "F");
		}

		//agua
		if (aleatorio_i == 3){
			copiastr(conjunto_atributos[contador_1], "A");
		}

		contador_1++;
	}

	//shuffle no vetor!
	int numeros[tamanho_arena];
	int contador_4 = 0;

	while(contador_4 < tamanho_arena){
		numeros[contador_4] = contador_4 + 1;
		contador_4++;
	}

	randomize (numeros, tamanho_arena);

	//imprimindo o vetor embaralhado linha por linha
	char vetor_shuffle[tamanho_arena][8];
	int contador_5 = 0;
	FILE *f = fopen("Terreno.txt", "w");
	while(contador_5 < tamanho_arena){
		int numero = numeros[contador_5];
		copiastr(vetor_shuffle[contador_5], conjunto_atributos[numero]);
		fprintf(f, "%s\n", vetor_shuffle[contador_5]);
		contador_5++;
	}	
}