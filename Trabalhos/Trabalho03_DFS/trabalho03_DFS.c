#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "../../GrafosListaAdjacencias/grafos_lista_adjacencias.h"
#include "../../EstruturasDeDados/Pilha/pilha_encadeada.h"
#include "../../EstruturasDeDados/Fila/fila_encadeada.h"
#include "../../EstruturasDeDados/Lista/lista_encadeada.h"
#include "./trabalho03_DFS.h"

#define INFINITY INT_MAX/2

typedef struct node_v_{
    int vertex;
    int value;
    struct node_v_ *next;
    struct node_v_ *prev;
}NodeV;

typedef struct grafo_{
    NodeV *Adj;
    char colour; //W -> white; B -> black; G -> grey
    int n_vertices;
    int dist;
}Graph;

/* Todas as funções abaixo foram criadas para o Trabalho03
*/
void RecursiveDFS(Graph *G, int cur_index, List *L_White, Stack *S_Black){
    

    return;
}

void CountCompontentsDFS(Graph *G){

    if (G == NULL) return;

    List *L_White = CreateList();
    Stack *S_Black = CreateList();

    for(int i=0; i<G->n_vertices; i++){
        G[i].colour = 'W';
        AddLastElem(L_White, i);
    }

    int root;

    while(!IsEmpty(L_White)){
        root = RemoveFirstElemR(L_White);
        AddFirstElem(L_White, root);

        RecursiveDFS(G, root, L_White, S_Black);
        
    }
    
    return;
}
