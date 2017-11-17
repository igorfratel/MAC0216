#include "utils.h"

void Erro(char *msg) {
  fprintf(stderr,"%s\n", msg);
}

void Fatal(char *msg, int cod) {
  Erro(msg);
  exit(cod);
}