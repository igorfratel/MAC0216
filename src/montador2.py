#!/usr/bin/python3

"""
Lê, na entrada padrão, um programa na linguagem de montagem da máquina
virtual e retorna um programa em C que executa este programa.

Uso:
    ./montador entrada1...entradaN
"""
import sys

def parse_programs(*args):
    out = open("programas.c",'w')

    out.write('//Arquivo que conterá todos os arquivos de programa dos robôs\n'
          '//Será gerado pelo parser em python\n'
          '#include "programas.h" \n\n')

    out.write('int compilador(FILE *, INSTR *);\n')

    out.write( "//Database contém todos os nomes dos arquivos\n"
                "char *database[] = {\n")

    for x in range(1, len(args[0])):
        out.write('"'+args[0][x]+'"')
        if(x != len(args[0]) - 1):
            out.write(", \n")
        else:
            out.write("\n")

    out.write(  "\n};\n"
            "void devolve_programa(int prog_num, INSTR *commands) {\n"
            "    //Recebe o número do programa e devolve o programa correspondente\n"
            '    FILE *p = fopen(database[prog_num], "r");\n'
            "    compilador(p, commands);}\n")

parse_programs(sys.argv)



# Local variables:
# mode: python
# End:
