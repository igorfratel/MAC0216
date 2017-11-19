#ifndef __TYPES_H__
#define __TYPES_H__
#define VET_MAX 100
#define PILMAX 99
#define MAXMEM 100
#define TIMES_MAX 5


typedef struct Celula Celula;
typedef struct Maquina Maquina;
typedef struct Arena Arena;
typedef struct Pilha Pilha;

/* Códigos das instruções */
typedef enum {
  PUSH,
  POP,
  DUP,
  ADD,
  SUB,
  MUL,
  DIV,
  JMP,
  JIT,
  JIF,
  CALL,
  RET,
  EQ,
  GT,
  GE,
  LT,
  LE,
  NE,
  STO,
  RCL,
  END,
  PRN,
  STL,
  RCE,
  ALC,
  FRE,
  SAVE,
  REST,
  ATR,
  SYS,
  PUSHCELL
} OpCode;

/* Tipos dos operandos */
typedef enum {
  NUM,
  ACAO,
  VAR,
  CELULA
} Tipo;

/* Tipo de terreno */
typedef enum {
  PLANO,
  FLORESTA,
  AGUA,
  BASE
} Terreno;

/* Célula */
struct Celula {
  Terreno terreno;
  short int equipe;
  short int cristais;
  short int ocupado;
  Maquina *robo;
};

/* Operando */
typedef struct {
  Tipo t;
  union {
   	int n;
   	int ac;
   	int v;
    Celula cel;
  }val;
} OPERANDO;

struct Pilha {
  int topo;
  OPERANDO val[PILMAX+1];
};

/* Instrução */
typedef struct {
  OpCode instr;
  int op;
} INSTR;

struct Arena{
	Celula **matriz; //A arena é uma matriz de celulas
  Celula *bases[TIMES_MAX]; // Vetor de bases (que também estão na matriz)
	int x; //número de posições em cada linha da matriz
	int y; //número de posições em cada coluna da matriz
	Maquina *vetor_maq[VET_MAX]; //vetor de ponteiros para máquinas virtuais com tamanho VET_MAX
	int robos;
};

struct Maquina {
  int equipe;
  int imagem;
  int pos[2]; //coordenadas na arena da posicao do robo
  int cristais;
  int vida;
  Arena *arena;
  // nivel de ocupação do robô
  int ocupado;

  Pilha *pil;
  Pilha *exec;
  OPERANDO Mem[MAXMEM];
  INSTR *prog;
  OPERANDO rbp; //!!!
  OPERANDO ip;
};

#endif
