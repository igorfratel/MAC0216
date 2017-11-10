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
  ATR, //$$
  SYS
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
  //(10-11-2017)
  //ESTRADA,
  //MONTANHA,
  //RIO,
  //BASE
//*********
//EDITANDO
  PLANO
  FLORESTA
  RIO
  BASE
//*********
} Terreno;

/* Célula */
typedef struct {
  Terreno terreno;
  short int cristais;
  short int ocupado;
} Celula;

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

/* Instrução */
typedef struct {
  OpCode instr;
  int op;
} INSTR;

#endif
