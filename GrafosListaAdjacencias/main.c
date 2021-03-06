#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "grafos_lista_adjacencias.h"
#include "../EstruturasDeDados/Pilha/pilha_encadeada.h"
#include "../EstruturasDeDados/Fila/fila_encadeada.h"
#include "../EstruturasDeDados/Lista/lista_encadeada.h"
#include "../ReadPajek/read_pajek.h"

#define READLINE_BUFFER 4096

int main(int argc, char *argv[]){
    char *string = (char *) calloc(400, sizeof(char));

//    strcpy(string,"../Amostras/ArquivosDFS/dfs_teste.txt");
//    strcpy(string,"../Amostras/aula9_arquivos_pajek/trial_dir_cic.txt");
//   strcpy(string,"../Trabalhos/Trabalho03_DFS/exemplo3a/case3.pajek");
//   strcpy(string,"../Trabalhos/Trabalho03_DFS/exemplo3b/case1.pajek");
    strcpy(string,"../Amostras/amostra_pajek.txt");

    FILE *file;
    file = fopen(string,"r");

    int n_vertices = getNumVertices(file);

    Graph *G;
    G = CreateGraph(n_vertices); 

    readPajek(G, file);
//    PrintGraph(G);

    DFS(G,3);

    /*
    printf("VerticeDeg 4: %d\n", VerticeDeg(G, 4));
    printf("IsEulerian: %d\n", IsEulerian(G));

    elem e = 2;
    */

    PrintGraph(G);

    FreeGraph(G);
    fclose(file);
    free(string);

    return 0;
}
