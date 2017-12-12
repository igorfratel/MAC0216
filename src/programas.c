//Arquivo que conterá todos os arquivos de programa dos robôs
//Será gerado pelo parser em python
#include "programas.h"

//INSTR comand[2000];
int compilador(FILE *, INSTR *);
//Database contém todos os nomes dos arquivos
char *database[] = {
"./programasteste/comandos/prog0.txt",
"./programasteste/comandos/prog1.txt",
"./programasteste/comandos/prog2.txt",
"./programasteste/comandos/prog3.txt",
"./programasteste/comandos/prog4.txt",
//"./programasteste/testes/fibo",
//"./programasteste/testes/aux"
};

INSTR *devolve_programa(int prog_num, INSTR comand[]) {
    //Recebe o número do programa e devolve o programa correspondente	
	FILE *p = fopen(database[prog_num], "r");
    int res = compilador(p, comand);
    if (res) return NULL;
    return comand;
}
