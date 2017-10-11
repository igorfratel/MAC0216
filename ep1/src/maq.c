#include <stdio.h>
#include <stdlib.h>
#include "maq.h"

/* #define DEBUG */

#ifdef DEBUG
#  define D(X) X
char *CODES[] = {
  "PUSH",
  "POP",
  "DUP",
  "ADD",
  "SUB",
  "MUL",
  "DIV",
  "JMP",
  "JIT",
  "JIF",
  "CALL",
  "RET",
  "EQ",
  "GT",
  "GE",
  "LT",
  "LE",
  "NE",
  "STO",
  "RCL",
  "END",
  "PRN",
  "STL", //!!!
  "RCE", //!!!
  "FRE", //!!!
  "ALC", //!!!
  "SAVE", //!!!
  "REST", //!!!
  "ATR" //$$
};
#else
#  define D(X)
#endif

static void Erro(char *msg) {
  fprintf(stderr, "%s\n", msg);
}

static void Fatal(char *msg, int cod) {
  Erro(msg);
  exit(cod);
}

Maquina *cria_maquina(INSTR *p) {
  Maquina *m = (Maquina*)malloc(sizeof(Maquina));
  if (!m) Fatal("Memória insuficiente",4);
  m->ip.t = NUM;//@@
  m->ip.n = 0;//@@
  m->prog = p;
  m->rbp.t = NUM;//@@
  m->rbp.n = 0; //!!!
  return m;
}

void destroi_maquina(Maquina *m) {
  free(m);
}

/* Alguns macros para facilitar a leitura do código */
#define ip (m->ip)
#define pil (&m->pil)
#define exec (&m->exec)
#define prg (m->prog)
#define rbp (m->rbp)

void exec_maquina(Maquina *m, int n) {
  int i;

  for (i = 0; i < n; i++) {
	OpCode   opc = prg[ip].instr;
	OPERANDO arg = prg[ip].op;

	D(printf("%3d: %-4.4s %d\n     ", ip, CODES[opc], arg));

	switch (opc) {
	  OPERANDO tmp;
    OPERANDO tmp1;
	case PUSH:
	  empilha(pil, arg);
	  break;
	case POP:
	  desempilha(pil);
	  break;
	case DUP:
	  tmp = desempilha(pil);
	  empilha(pil, tmp);
	  empilha(pil, tmp);
	  break;
	case ADD://@@@
    tmp = desempilha(pil);
    tmp1 = desempilha(pil);
    if(tmp.t == tmp1.t) {
      tmp.n += tmp1.n;
      empilha(pil, tmp);
    }
    else
      Erro("nao e possivel somar dois tipos diferentes de dados");

	  break;
	case SUB://@@@
	  tmp = desempilha(pil);
    tmp1 = desempilha(pil);
    if(tmp.t == tmp1.t){
      tmp1.n -= tmp.n;
      empilha(pil, tmp1);
    }
    else
      Erro("nao e possivel realizar subtrair dois tipos diferentes de dados");
	  break;
	case MUL://@@@@
    tmp = desempilha(pil);
    tmp1 = desempilha(pil);
    if(tmp.t == tmp1.t) {
      tmp.n *= tmp1.n;
      empilha(pil, tmp);
    }
    else
      Erro("nao e possivel realizar multiplicacao entre dois tipos diferentes de dados");
	  break;
	case DIV://@@@
	  tmp = desempilha(pil);
    tmp1 = desempilha(pil);
    if(tmp.t == tmp1.t){
      tmp1.n /= tmp.n;
      empilha(pil, tmp1);
    }
    else
      Erro("nao e possivel realizar divisao entre dois tipos diferentes de dados");
	  break;
  // não sei se o ip recebe um tipo que não seja NUM
	case JMP:
      ip.n = arg.n;
      continue;
	case JIT:
    tmp = desempilha(pil);
	  if (tmp.n != 0) {
  		ip.n = arg.n;
  		continue;
	  }
	  break;
	case JIF:
  tmp = desempilha(pil);
	  if (tmp.n == 0) {
		ip.n = arg.n;
		continue;
	  }
	  break;
	case CALL:
	  empilha(exec, ip);
	  empilha(exec, rbp); //!!! SAVE
	  rbp.n = exec->topo - 1; //!!! SAVE
	  ip.n = arg.n;
	  continue;
	case RET:
	  rbp = desempilha(exec); //!!! REST
	  ip = desempilha(exec);
	  break;
  //testar para ver se funciona sem o uso de tmp e tmp1
	case EQ:
    tmp.t = NUM;
	  if (desempilha(pil).n == desempilha(pil).n) {
      tmp.n = 1;
      empilha(pil, tmp);
    }
	  else{
      tmp.n = 0;
      empilha(pil, tmp);
    }
	  break;
	case GT:
    tmp.t = NUM;
	  if (desempilha(pil).n < desempilha(pil).n) {
      tmp.n = 1;
      empilha(pil, tmp);
    }
	  else{
      tmp.n = 0;
      empilha(pil, tmp);
    }
	  break;
	case GE:
	  if (desempilha(pil) <= desempilha(pil))
		empilha(pil, 1);
	  else
		empilha(pil, 0);
	  break;
	case LT:
	  if (desempilha(pil) > desempilha(pil))
		empilha(pil, 1);
	  else
		empilha(pil, 0);
	  break;
	case LE:
	  if (desempilha(pil) >= desempilha(pil))
		empilha(pil, 1);
	  else
		empilha(pil, 0);
	  break;
	case NE:
	  if (desempilha(pil) != desempilha(pil))
		empilha(pil, 1);
	  else
		empilha(pil, 0);
	  break;
	case STO:
	  m->Mem[arg] = desempilha(pil);
	  break;
	case RCL:
	  empilha(pil,m->Mem[arg]);
	  break;
	case STL: //!!!
	  exec->val[arg + rbp] = desempilha(pil);
	  break;
	case RCE: //!!!
		empilha(pil, exec->val[arg + rbp]);
		break;
	case ALC: //!!! malloc
		exec->topo = exec->topo + arg;
		break;
	case FRE: //!!! free
		exec->topo = exec->topo - arg;
		break;
	case SAVE: //!!!
		empilha(exec, rbp);
		rbp = exec->topo - 1;
		break;
	case REST: //!!!
		rbp = desempilha(exec);
		break;
	case END:
	  return;
	case PRN:
	  printf("%d\n", desempilha(pil));
	  break;
	case ATR: //$$
	  break; 

	}
	D(imprime(pil,5));
	D(puts("\n"));

	ip++;
  }
}
