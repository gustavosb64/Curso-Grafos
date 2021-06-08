#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "../../GrafosListaAdjacencias/grafos_lista_adjacencias.h"
#include "../../EstruturasDeDados/Pilha/pilha_encadeada.h"
#include "../../EstruturasDeDados/Fila/fila_encadeada.h"
#include "../../EstruturasDeDados/Lista/lista_encadeada.h"

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

/* Ambas as funções abaixo foram criadas para o Trabalho2
 * Imprimem matriz de distâncias relativas a cada vértice
*/
void CheckDistanceBFS(Graph *G, elem e){

    List *L_White = CreateList();
    List *L_Black = CreateList();
    Queue *Q_Grey = CreateQueue();

    for(int i=0; i<G->n_vertices; i++){
        AddLastElem(L_White, i);
        G[i].colour = 'W';
        G[i].dist = INFINITY;
    }
    AddElemQueue(Q_Grey, e);
    G[e].colour = 'G';
    G[e].dist = 0;

    int aux_e;
    int q_index;
    while(!IsEmptyQueue(Q_Grey)){
        OutQueue(Q_Grey, &q_index); 
        NodeV *aux_v = G[q_index].Adj;
        while (aux_v != NULL){
            if (G[aux_v->vertex].colour == 'W'){
                AddElemQueue(Q_Grey, aux_v->vertex);
                G[aux_v->vertex].colour = 'G';
                G[aux_v->vertex].dist = G[q_index].dist + 1;
                SearchRemoveElem(L_White, &aux_v->vertex, &aux_e);
            }
            aux_v = aux_v->next;
        }
        G[q_index].colour = 'B';
        AddLastElem(L_Black, q_index);
    }

    FreeList(L_White);
    FreeList(L_Black);
    FreeQueue(Q_Grey);

    return;
}

void PrintBFS(Graph *G){
    
    for (int j=0; j<G->n_vertices; j++){
        CheckDistanceBFS(G, j);
        for(int i=0; i<G->n_vertices; i++){
            printf("%d ",G[i].dist);
        }    
        printf("\n");
    }
}
