D [0-9]
L [a-zA-Z_]
H [a-zA-Z_0-9]
E [Ee][+-]?{D}+ 
%option noyywrap
%{
#include <math.h>
#include "compila.tab.h"
%}


%%
{D}*[.]?{D}+{E}?	{ yylval.val = atof(yytext); return NUMt; }

ret(urn)?  { return RETt; }

if      { return IF; }
else    { return ELSE; }
while	{ return WHILE; }
func|def { return FUNC; }
print   { return PRINT; }

CRI_CIMA  { return CRI_CIMAt; } 
CRI_DSUP  { return CRI_DSUPt; }
CRI_DINF  { return CRI_DINFt; }
CRI_BAIXO { return CRI_BAIXOt;} 
CRI_EINF  { return CRI_EINFt; }
CRI_ESUP  { return CRI_ESUPt; }

REC_CIMA  { return REC_CIMAt; } 
REC_DSUP  { return REC_DSUPt; }
REC_DINF  { return REC_DINFt; }
REC_BAIXO { return REC_BAIXOt;}
REC_EINF  { return REC_EINFt; }
REC_ESUP  { return REC_ESUPt; }

MOV_CIMA  { return MOV_CIMAt; }
MOV_DSUP  { return MOV_DSUPt; }
MOV_DINF  { return MOV_DINFt; }
MOV_BAIXO { return MOV_BAIXOt;}
MOV_EINF  { return MOV_EINFt; }
MOV_ESUP  { return MOV_ESUPt; }

ATQ_CIMA  { return ATQ_CIMAt; }
ATQ_DSUP  { return ATQ_DSUPt; }
ATQ_DINF  { return ATQ_DINFt; }
ATQ_BAIXO { return ATQ_BAIXOt;}
ATQ_EINF  { return ATQ_EINFt; }
ATQ_ESUP  { return ATQ_ESUPt; }

DEP_CIMA  { return DEP_CIMAt; }
DEP_DSUP  { return DEP_DSUPt; }
DEP_DINF  { return DEP_DINFt; }
DEP_BAIXO { return DEP_BAIXOt;}
DEP_EINF  { return DEP_EINFt; }
DEP_ESUP  { return DEP_ESUPt; }

{L}{H}* {
  strncpy(yylval.cod, yytext, 30);
  return ID;
}

[ \t\n]+	/* pula espacos em branco */

#.*		/* comentarios simples */

;		{ return EOL; }
,		{ return SEP; }
=		{ return ASGN; }
[(]		{ return OPEN; }
[)]		{ return CLOSE; }
[{]		{ return ABRE; }
[}]		{ return FECHA; }
[+]		{ return ADDt; }
[-]		{ return SUBt; }
[*]		{ return MULt; }
[/]		{ return DIVt; }
==		{ return EQt; }
!=		{ return NEt; }
"<"		{ return LTt; }
"<="	{ return LEt; }
">"		{ return GTt; }
">="	{ return GEt; }

.	{  fprintf(stderr, "Entrada ignorada\n-->%s\n", yytext); }

%%

/* Local Variables: */
/* mode: c */
/* End: */
