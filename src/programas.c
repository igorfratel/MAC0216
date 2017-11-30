//Arquivo que conterá todos os programas dos robôs em jogo
//Será gerado pelo parser em python
#include "programas.h"
INSTR prog0[] = {
  {PUSH, 0}
  ,{SYS, 0}
  ,{PUSH, 2}
  ,{SYS, 0}
  ,{PUSH, 4}
  ,{SYS, 0}
  ,{PUSH, 0}
  ,{SYS, 0}
  ,{PUSH, 2}
  ,{SYS, 0}
  ,{PUSH, 4}
  ,{SYS, 0}
  ,{PUSH, 0}
  ,{SYS, 0}
  ,{PUSH, 2}
  ,{SYS, 0}
  ,{PUSH, 4}
  ,{SYS, 0}
  ,{PUSH, 0}
  ,{SYS, 0}
  ,{PUSH, 2}
  ,{SYS, 0}
  ,{PUSH, 4}
  ,{SYS, 0}
  ,{PUSH, 0}
  ,{SYS, 0}
  ,{PUSH, 2}
  ,{SYS, 0}
  ,{PUSH, 4}
  ,{SYS, 0}
  ,{PUSH, 0}
  ,{SYS, 0}
  ,{PUSH, 2}
  ,{SYS, 0}
  ,{PUSH, 4}
  ,{SYS, 0}
  ,{PUSH, 0}
  ,{SYS, 0}
  ,{PUSH, 2}
  ,{SYS, 0}
  ,{PUSH, 4}
  ,{SYS, 0}
  ,{PUSH, 0}
  ,{SYS, 0}
  ,{PUSH, 2}
  ,{SYS, 0}
  ,{PUSH, 4}
  ,{SYS, 0}
  ,{END, 0}
};
INSTR prog1[] = {
  {PUSH, 0}
  ,{SYS, 0}
  ,{PUSH, 2}
  ,{SYS, 0}
  ,{PUSH, 4}
  ,{SYS, 0}
  ,{PUSH, 0}
  ,{SYS, 0}
  ,{PUSH, 2}
  ,{SYS, 0}
  ,{PUSH, 4}
  ,{SYS, 0}
  ,{PUSH, 0}
  ,{SYS, 0}
  ,{PUSH, 2}
  ,{SYS, 0}
  ,{PUSH, 4}
  ,{SYS, 0}
  ,{PUSH, 0}
  ,{SYS, 0}
  ,{PUSH, 2}
  ,{SYS, 0}
  ,{PUSH, 4}
  ,{SYS, 0}
  ,{PUSH, 0}
  ,{SYS, 0}
  ,{PUSH, 2}
  ,{SYS, 0}
  ,{PUSH, 4}
  ,{SYS, 0}
  ,{PUSH, 0}
  ,{SYS, 0}
  ,{PUSH, 2}
  ,{SYS, 0}
  ,{PUSH, 4}
  ,{SYS, 0}
  ,{PUSH, 0}
  ,{SYS, 0}
  ,{PUSH, 2}
  ,{SYS, 0}
  ,{PUSH, 4}
  ,{SYS, 0}
  ,{PUSH, 0}
  ,{SYS, 0}
  ,{PUSH, 2}
  ,{SYS, 0}
  ,{PUSH, 4}
  ,{SYS, 0}
  ,{END, 0}
};
//Database contém todos os vetores de programas
INSTR *database[] = {
  prog0,
  prog1
};
INSTR *devolve_programa(int prog_num) {
  //Recebe o número do programa e devolve o programa correspondente
  return database[prog_num];
}