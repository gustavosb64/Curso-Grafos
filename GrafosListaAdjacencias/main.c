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
//    file = fopen("../Amostras/ArquivosDFS/dfs_teste.txt","r");
//    file = fopen("../Amostras/aula9_arquivos_pajek/trial_dir_cic.txt","r");
    file = fopen("../Trabalhos/Trabalho03_DFS/exemplo3a/case1.pajek","r");

    int n_vertices = getNumVertices(file);

    Graph *G;
    G = CreateGraph(n_vertices); 

    readPajek(G, file);
    PrintGraph(G);

    DFS(G,3);

    /*
    printf("VerticeDeg 4: %d\n", VerticeDeg(G, 4));
    printf("IsEulerian: %d\n", IsEulerian(G));

    elem e = 2;
    */

    FreeGraph(G);
    fclose(file);

    return 0;
}
