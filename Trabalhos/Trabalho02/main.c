#include <stdio.h>
#include <stdlib.h>
#include "grafos_lista_adjacencias.h"
#include "../../EstruturasDeDados/Pilha/pilha_encadeada.h"
#include "../../EstruturasDeDados/Fila/fila_encadeada.h"
#include "../../EstruturasDeDados/Lista/lista_encadeada.h"
#include "./read_pajek.h"

#define READLINE_BUFFER 4096

int main(int argc, char *argv[]){

    char *string;
    string = readline(stdin);

    FILE *file;
    file = fopen("grafo1.pajek","r");

    int n_vertices = getNumVertices(file);

    Graph *G;
    G = CreateGraph(n_vertices); 

    readPajek(G, file);

    PrintBFS(G);

    FreeGraph(G);
    fclose(file);
    free(string);

    return 0;
}
