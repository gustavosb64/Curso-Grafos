#include <stdio.h>
#include <stdlib.h>
#include "grafos_lista_adjacencias.h"
#include "../EstruturasDeDados/Pilha/pilha_encadeada.h"
#include "../EstruturasDeDados/Fila/fila_encadeada.h"
#include "../EstruturasDeDados/Lista/lista_encadeada.h"
#include "../ReadPajek/read_pajek.h"

#define READLINE_BUFFER 4096

int main(int argc, char *argv[]){

    FILE *file;
    file = fopen("../Amostras/amostra_pajek.txt","r");

    int n_vertices = getNumVertices(file);

    Graph *G;
    G = CreateGraph(n_vertices); 

    readPajek(G, file);
    PrintGraph(G);

    printf("VerticeDeg 4: %d\n", VerticeDeg(G, 4));
    printf("IsEulerian: %d\n", IsEulerian(G));

    elem e = 2;
    BFS(G,7);

    FreeGraph(G);
    fclose(file);

    return 0;
}
