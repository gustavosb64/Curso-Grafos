#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "grafos_lista_adjacencias.h"
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

Graph* CreateGraph(int n_vertices){
    Graph *G = (Graph *) malloc(n_vertices * sizeof(Graph));
    if (G == NULL) return NULL;
    
    G->n_vertices = n_vertices;

    for (int i=0; i<n_vertices; i++){
        G[i].Adj = NULL; 
        G[i].colour = 'W'; 
        G[i].dist = INFINITY;
    }

    return G;
}

int IsEmpty(NodeV *Adj){
    if (Adj == NULL) return 1; 
    else return 0;
}

int Insert(Graph *G, int g_src, int g_dest, int value){

    if (G[g_src].Adj == NULL){
        G[g_src].Adj = (NodeV *) malloc(sizeof(NodeV)); 
        G[g_src].Adj->vertex = g_dest;
        G[g_src].Adj->value = value;
        G[g_src].Adj->next = NULL;
        G[g_src].Adj->prev = NULL;

        return 0;
    }

    NodeV *aux_edge = G[g_src].Adj;
    while (aux_edge->next != NULL){
        if (aux_edge->vertex == g_dest) return 1;
        aux_edge = aux_edge->next;
    }
   
    NodeV *new_edge = (NodeV *) malloc(sizeof(NodeV));
    new_edge->vertex = g_dest;
    new_edge->value = value;
    new_edge->next = NULL;
    new_edge->prev = aux_edge;
    
    aux_edge->next = new_edge;

    return 0;
}   

void PrintGraph(Graph *G){
    NodeV *aux;
    
    for (int i=0; i<G->n_vertices; i++){
        if (G[i].Adj != NULL){
            printf("Vertex: %d\n",i+1);
            aux = G[i].Adj;
            while (aux != NULL){
                printf(" |-> %d\n",aux->vertex+1);
                aux = aux->next; 
            }
        }
    }
 
    return;
}

void FreeGraph(Graph *G){
    NodeV *aux;
    NodeV *aux2;
    
    for (int i=0; i<G->n_vertices; i++){
        if (G[i].Adj != NULL){
            aux = G[i].Adj;
            while (aux != NULL){
                aux2 = aux;
                aux = aux->next;
                free(aux2);
            }
            G[i].Adj = NULL;
        }
    }

    free(G);
    return;
}

void BFS (Graph *G, elem e){

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
        BFS(G, j);
        for(int i=0; i<G->n_vertices; i++){
            printf("%d ",G[i].dist);
        }    
        printf("\n");
    }
 
    return;
}
