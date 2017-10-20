#include "pilha.h"

static void Erro(char *msg) {
  fprintf(stderr,"%s\n", msg);
}

static void Fatal(char *msg, int cod) {
  Erro(msg);
  exit(cod);
}


Pilha *cria_pilha() {
  Pilha *p = (Pilha*)malloc(sizeof(Pilha));
  if (!p) Fatal("Memória insuficiente",4);
  p->topo = 0;
  return p;
}

void destroi_pilha(Pilha *p) {
  free(p);
}

void empilha(Pilha *p, OPERANDO op) {
  if (p->topo < PILMAX)
	p->val[p->topo++] = op;
  else Erro("Pilha cheia");
}

OPERANDO desempilha(Pilha *p) {
  if (p->topo > 0)
	return p->val[--p->topo];
  else Erro("Pilha vazia");
  OPERANDO lixo; //O compilador precisa que a função retorne um OPERANDO
  return lixo;
}

void imprime(Pilha *p, int n) {
  int t = p->topo-1;
  int i;
  printf("[");
  for (i = t; i >= 0 && i > p->topo-n; i--) {
   switch (p->val[i].t) {
    case(NUM):
	   printf("NUM %4d, ", p->val[i].val.n);
     break;
    case(ACAO):
     printf("ACAO %4d, ", p->val[i].val.ac);
     break;
    case(VAR):
     printf("VAR %4d, ", p->val[i].val.v);
     break;
    case(CELULA):
      printf("Terreno: %4d, ", p->val[i].val.cel.terreno); //terreno
      printf("Cristais: %4d, ", p->val[i].val.cel.cristais); //cristais
      if (p->val[i].val.cel.ocupado) printf("Ocupado\n"); //ocupado
      else printf("Livre\n");//livre
     break;
    
   }
    
  } 
  printf("]");
  return;
}
