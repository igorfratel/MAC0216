//Arquivo que conterá todos os arquivos de programa dos robôs
//Será gerado pelo parser em python
#include "programas.h" 

INSTR p1[2000];
int compilador(FILE *, INSTR *);
//Database contém todos os nomes dos arquivos
char *database[] = {
"./programasteste/testes/fatorial", 
"./programasteste/testes/fibo", 
"./programasteste/testes/aux"

};
INSTR *devolve_programa(int prog_num) {
    //Recebe o número do programa e devolve o programa correspondente
    FILE *p = fopen(database[prog_num], "r");
    int res = compilador(p, p1);
    if (res) return NULL;
    return p1;
}