#include <stdio.h>
#include <stdlib.h>
#include "../../GrafosListaAdjacencias/grafos_lista_adjacencias.h"
#include "../../EstruturasDeDados/Pilha/pilha_encadeada.h"
#include "../../EstruturasDeDados/Fila/fila_encadeada.h"
#include "../../EstruturasDeDados/Lista/lista_encadeada.h"
#include "../../ReadPajek/read_pajek.h"
#include "./trabalho03_DFS.h"

#define READLINE_BUFFER 4096

int main(int argc, char *argv[]){

    char *string;
    string = readline(stdin);

    FILE *file;
    file = fopen(string,"r");

    int n_vertices = getNumVertices(file);

    Graph *G;
    G = CreateGraph(n_vertices); 

    readPajek(G, file);

    FreeGraph(G);
    fclose(file);
    free(string);

    return 0;
}
