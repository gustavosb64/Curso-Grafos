#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "../../GrafosListaAdjacencias/grafos_lista_adjacencias.h"
#include "../../EstruturasDeDados/Pilha/pilha_encadeada.h"
#include "../../EstruturasDeDados/Fila/fila_encadeada.h"
#include "../../EstruturasDeDados/Lista/lista_encadeada.h"
#include "../../ReadPajek/read_pajek.h"
#include "./trabalho03_DFS.h"

#define READLINE_BUFFER 4096

int main(int argc, char *argv[]){
    char *string = (char *) calloc(400, sizeof(char));
    scanf(" %s", string);

    FILE *file;
    file = fopen(string,"r");

    int n_vertices = getNumVertices(file);

    Graph *G;
    G = CreateGraph(n_vertices); 

    readPajek(G, file);

//    PartA_DFS(G);
    PartB_DFS(G);

    FreeGraph(G);
    fclose(file);
    free(string);

    return 0;
}
