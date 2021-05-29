#include <stdio.h>
#include <stdlib.h>
#include "grafos_lista_adjacencias.h"
#include "../../EstruturasDeDados/Pilha/pilha_encadeada.h"
#include "../../EstruturasDeDados/Fila/fila_encadeada.h"
#include "../../EstruturasDeDados/Lista/lista_encadeada.h"
#include "./read_pajek.h"

#define READLINE_BUFFER 4096

int main(int argc, char *argv[]){

    FILE *file;
    file = fopen("grafo3.pajek","r");

    int n_vertices = getNumVertices(file);
    printf("n_vertices: %d\n",n_vertices);

    Graph *G;
    G = CreateGraph(n_vertices); 

    readPajek(G, file);
    PrintGraph(G);

    printf("VerticeDeg 4: %d\n", VerticeDeg(G, 3));
    printf("IsEulerian: %d\n", IsEulerian(G));

    elem e = 0;

    for (int i=0; i<5; i++){
        printf("%d ",BFS(G, i)); 
//        printf("$$$$$$%d\n",BFS(G, i)); 
    }

//    int** M = BFS(G, e);

//    PrintMat(M, G);
//    FreeMat(M, G);

    FreeGraph(G);
    fclose(file);
    return 0;
}
