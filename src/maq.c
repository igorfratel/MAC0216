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
  //"STL", //!!!
  //"RCE", //!!!
  //"FRE", //!!!
  //"ALC", //!!!
  //"SAVE", //!!!
  //"REST", //!!!
  "ATR", //$$
  "SYS",
  "PUSHCELL",
  //"STS",
  //"RCS",
  "ENTRY",
  "LEAVE"
};
#else
#  define D(X)
#endif

Maquina *cria_maquina(INSTR *p) {
  int imagem;
	//escolhe a imagem do robô de maneira aleatória
	srand(time(NULL));
	imagem = rand() % 8;
  imagem++;

  Maquina *m = (Maquina*)malloc(sizeof(Maquina));
  if (!m) Fatal("Memória insuficiente",4);
  m->ip.t = NUM;//@@
  m->ip.val.n = 0;//@@
  m->prog = p;
  m->ib.t = NUM;//@@
  m->ib.val.n = 0; //!!!
  m->ocupado = 0;
  m->vida = 10;
  m->imagem = imagem;
  m->cristais = 0;
  m->pil = cria_pilha();
  m->exec = cria_pilha();
  return m;
}

void destroi_maquina(Maquina *m) {
  free(m);
}

int new_frame(Maquina *m, int n) {
  int ibc = m->ib.val.n;
  if (ibc < MAXFRM-1) {
    m->bp[++m->ib.val.n] = n+ibc;
    return m->ib.val.n;
  }
  return -1;
}

int del_frame(Maquina *m) {
  if (m->ib.val.n > 0) return --m->ib.val.n;
  return -1;
}

/* Alguns macros para facilitar a leitura do código */
#define ip (m->ip)
#define pil (m->pil)
#define exec (m->exec)
#define prg (m->prog)
#define ib (m->ib)
#define bp (m->bp)

void exec_maquina(Maquina *m, int n) {
  int i;

  for (i = 0; i < n; i++) {
	OpCode   opc = prg[ip.val.n].instr;
	OPERANDO arg; //Cria operando
  arg.t = NUM; //O operando sempre vai ser um NUM
  arg.val.n = prg[ip.val.n].op; //Preenche o valor do operando
	D(printf("%3d: %-4.4s %d\n     ", ip.val.n, CODES[opc], arg));
  int *posicao;

  switch (opc) {
	  OPERANDO tmp;
    OPERANDO tmp2;
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
	case ADD:
    tmp = desempilha(pil);
    tmp2 = desempilha(pil);
    if(tmp.t == NUM && tmp2.t == NUM) { //Só funciona com NUM
      tmp.val.n += tmp2.val.n;
      empilha(pil, tmp);
    }
    else { //Devolve a pilha no estado em que recebeu
      empilha(pil, tmp2);
      empilha(pil, tmp);
      Erro("(ADD): Dados incompatíveis");
    }
	  break;
	case SUB:
	  tmp = desempilha(pil);
    tmp2 = desempilha(pil);
    if(tmp.t == NUM && tmp2.t == NUM){
      tmp2.val.n -= tmp.val.n;
      empilha(pil, tmp2);
    }
    else { //Devolve a pilha no estado em que recebeu
      empilha(pil, tmp2);
      empilha(pil, tmp);
      Erro("(SUB): Dados incompatíveis");
    }
	  break;
	case MUL:
    tmp = desempilha(pil);
    tmp2 = desempilha(pil);
    if(tmp.t == NUM && tmp2.t == NUM) {
      tmp.val.n *= tmp2.val.n;
      empilha(pil, tmp);
    }
    else { //Devolve a pilha no estado em que recebeu
      empilha(pil, tmp2);
      empilha(pil, tmp);
      Erro("(MUL): Dados incompatíveis");
    }
	  break;
	case DIV:
	  tmp = desempilha(pil);
    tmp2 = desempilha(pil);
    if(tmp.t == NUM && tmp2.t == NUM){
      tmp2.val.n /= tmp.val.n;
      empilha(pil, tmp2);
    }
    else { //Devolve a pilha no estado em que recebeu
      empilha(pil, tmp2);
      empilha(pil, tmp);
      Erro("(DIV): Dados incompatíveis");
    }
	  break;
	case JMP:
        ip.val.n = arg.val.n;
        continue;
	case JIT:
    tmp = desempilha(pil);
    if (tmp.t == NUM && tmp.val.n != 0) {
  		  ip.val.n = arg.val.n;
  	 	  continue;
    }
    else if (tmp.t != NUM){
      empilha(pil, tmp); //Devolve a pilha no estado em que recebeu
      Erro("(JIT): Dado incompatível");
    }
	  break;
	case JIF:
    tmp = desempilha(pil);
	  if (tmp.t == NUM && tmp.val.n == 0) {
		  ip.val.n = arg.val.n;
		  continue;
	  }
    else if (tmp.t != NUM) {
      empilha(pil, tmp); //Devolve a pilha no estado em que recebeu
      Erro("(JIF): Dado incompatível");
    }
	  break;
	case CALL:
	  empilha(exec, ip);
	  ip.val.n = arg.val.n;
	  continue;
	case RET:
    tmp = desempilha(exec);
    if (tmp.t == NUM) {
	   ip = tmp;
    }
    else {
      empilha(pil, tmp);
      Erro("(RET): Dados incompatíveis");
    }
	  break;
	case EQ:
    tmp = desempilha(pil);
    tmp2 = desempilha(pil);
	  if (tmp.t == NUM && tmp2.t == NUM && tmp.val.n == tmp2.val.n) { //Verifica se são números e se são iguais
      tmp.val.n = 1;
      empilha(pil, tmp);
    }
	  else { //Retorna 0 caso os números sejam diferentes ou caso os tipos dos operandos sejam diferentes
      tmp.val.n = 0;
      empilha(pil, tmp);
    }
	  break;
	case GT:
    tmp = desempilha(pil);
    tmp2 = desempilha(pil);
    if (tmp.t == NUM && tmp2.t == NUM && tmp.val.n < tmp2.val.n) {
      tmp.val.n = 1;
      empilha(pil, tmp);
    }
	  else {
      tmp.val.n = 0;
      empilha(pil, tmp);
    }
	  break;
	case GE:
    tmp = desempilha(pil);
    tmp2 = desempilha(pil);
    if (tmp.t == NUM && tmp2.t == NUM && tmp.val.n <= tmp2.val.n) {
      tmp.val.n = 1;
      empilha(pil, tmp);
    }
	  else{
      tmp.val.n = 0;
		  empilha(pil, tmp);
    }
	  break;
	case LT:
    tmp = desempilha(pil);
    tmp2 = desempilha(pil);
    if (tmp.t == NUM && tmp2.t == NUM && tmp.val.n > tmp2.val.n) {
      tmp.val.n = 1;
      empilha(pil, tmp);
    }
	  else {
      tmp.val.n = 0;
	    empilha(pil, tmp);
    }
	  break;
	case LE:
    tmp = desempilha(pil);
    tmp2 = desempilha(pil);
    if (tmp.t == NUM && tmp2.t == NUM && tmp.val.n >= tmp2.val.n) {
      tmp.val.n = 1;
	    empilha(pil, tmp);
    }
	  else {
      tmp.val.n = 0;
	    empilha(pil, tmp);
    }
	  break;
	case NE:
    tmp = desempilha(pil);
    tmp2 = desempilha(pil);
    if (tmp.t == NUM && tmp2.t == NUM && tmp.val.n != tmp2.val.n) {
      tmp.val.n = 1;
	    empilha(pil, tmp);
    }
	  else {
      tmp.val.n = 0;
	    empilha(pil, tmp);
    }
	  break;
	case STO:
    m->Mem[arg.val.n + bp[ib.val.n]] = desempilha(pil);
	  break;
	case RCL:
    empilha(pil,m->Mem[arg.val.n + bp[ib.val.n]]);
	  break;
	case END:
    pil->topo = 0;
	  return;
	case PRN:
    tmp = desempilha(pil);
    switch (tmp.t) {
      case NUM:
        printf("%d\n", tmp.val.n);
        break;
      case ACAO:
        printf("%d\n", tmp.val.ac);
        break;
      case VAR:
        printf("%d\n", tmp.val.v);
        break;
      case CELULA:
        printf("Terreno: %d, ", tmp.val.cel.terreno); //terreno
        printf("Cristais: %d, ", tmp.val.cel.cristais); //cristais
        if (tmp.val.cel.ocupado) printf("Ocupado\n"); //ocupado
        else printf("Livre\n");//livre
        break;
    }
	  break;
	case ATR:
    tmp = desempilha(pil);
    tmp2.t = NUM;
    if (tmp.t == CELULA) { //É uma célula
      switch(arg.val.n) { //Qual argumento da célula você quer?
        case 0: //terreno
          tmp2.val.n = tmp.val.cel.terreno; //nota: caso seja uma base, retorna 3
        case 1: //cristais
          tmp2.val.n = tmp.val.cel.cristais;
        case 2: //ocupado
          tmp2.val.n = tmp.val.cel.ocupado;
        case 3:
          if (tmp.val.cel.terreno == BASE) tmp2.val.n = 1; //devolve 1 caso seja uma base
          else tmp2.val.n = 0; // 0, c.c
      }
      empilha(pil, tmp2);
    }
    else { //Não é uma célula
      empilha(pil, tmp); //Devolve a pilha no estado original
      Erro("(ATR): Dado incompatível");
    }
    break;

  case SYS:
    Sistema(m->arena, arg.val.n, m);
    break;

  case PUSHCELL:
    //Recebe como argumento uma direção, empilha a célula adjacente ao robô que corresponde a essa direção.
    //Caso a célula não exista(por exemplo, se o robô estiver em uma borda), empilha -1.
    posicao = busca_celula(m->arena, m, arg.val.n);
    if(posicao[0] != -1) {
      tmp.t = CELULA;
      tmp.val.cel = m->arena->matriz[posicao[0]][posicao[1]];
      empilha(pil, tmp);
    }
    else {
      tmp.t = NUM;
      tmp.val.n = -1;
      empilha(pil, tmp);
    }
    break;
  case ENTRY:
    new_frame(m, arg.val.n);
    break;
  case LEAVE:
    del_frame(m);
    break;
  }

	D(imprime(pil,5));
	D(puts("\n"));

	ip.val.n++;
  }
}
