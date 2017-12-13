//Arquivo que conterá todos os arquivos de programa dos robôs
//Será gerado pelo parser em python
#include "programas.h" 

int compilador(FILE *, INSTR *);
//Database contém todos os nomes dos arquivos
char *database[] = {
"programasteste/comandos/prog0.txt", 
"programasteste/comandos/prog1.txt", 
"programasteste/comandos/prog2.txt"

};
void devolve_programa(int prog_num, INSTR *commands) {
    //Recebe o número do programa e devolve o programa correspondente
    FILE *p = fopen(database[prog_num], "r");
    compilador(p, commands);}
