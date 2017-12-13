#ifndef __PROGRAMAS_H__
#define __PROGRAMAS_H__

#include "types.h"
#include "maq.h"
#include "compila.tab.h"
//Recebe o número do programa e retorna o programa correspondente
void devolve_programa(int prog_num, INSTR *commands);

#endif
