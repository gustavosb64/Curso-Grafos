#ifndef READ_PAJEK_H
#define READ_PAJEK_H
#include "./grafos_lista_adjacencias.h"

int getNumVertices(FILE *);
void readPajek(Graph *, FILE *);
char* readline(FILE *);

#endif
