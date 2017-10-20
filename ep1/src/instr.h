#ifndef __INSTR_H__
#define __INSTR_H__

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
  STS,
  RCS,
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
  ATR //$$
} OpCode;

/* Tipos dos operandos */
typedef enum {
  NUM,
  ACAO,
  VAR,
  CELULA
} Tipo;

/* Operando */
typedef struct {
  Tipo t;
  union {
   	int n;
   	int ac;
   	int v;
    Celula cel;
  };
} OPERANDO;

/* Tipo de terreno */
typedef enum {
  ESTRADA,
  MONTANHA,
  RIO,
  BASE
} Terreno;

/* Célula */
typedef struct {
  Terreno terreno;
  short int cristais;
  short int ocupado;
} Celula;

/* Instrução */
typedef struct {
  OpCode instr;
  int op;
} INSTR;

#endif
