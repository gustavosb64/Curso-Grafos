#include <stdio.h>
#include <stdlib.h>
#include "grafos_lista_adjacencias.h"
#include "./Pilha/pilha_encadeada.h"

typedef struct node_v_{
    int vertex;
    int value;
    struct node_v_ *next;
    struct node_v_ *prev;
}NodeV;

typedef struct grafo_{
    NodeV *Adj;
    int n_vertices;
}Graph;

Graph* CreateGraph(int n_vertices){
    Graph *G = (Graph *) malloc(n_vertices * sizeof(Graph));
    if (G == NULL) return NULL;
    
    G->n_vertices = n_vertices;

    for (int i=0; i<n_vertices; i++) 
        G[i].Adj = NULL; 

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

int RemoveEdge(Graph *G, int g_src, int g_dest){
     
    if (G == NULL || (IsEmpty(G[g_src].Adj))) return 1;

    NodeV *n_aux = SearchAdj(G, g_src, g_dest);
    NodeV *n_aux_prev = n_aux->prev;

    if (n_aux_prev == NULL) G[g_src].Adj = n_aux->next;
    else n_aux_prev->next = n_aux->next;

    free(n_aux);

    return 0;
}

NodeV* SearchAdj(Graph *G, int g_src, int g_dest){
    
    if (G == NULL || (IsEmpty(G[g_src].Adj))) return NULL;
    
    NodeV *aux_adj = G[g_src].Adj; 
    while (aux_adj != NULL){
        if (aux_adj->vertex == g_dest) return aux_adj;
        aux_adj = aux_adj->next;
    } 

    return NULL;
}

//Retorna o grau do vertice
int VerticeDeg(Graph *G, int v){

    if (G[v].Adj == NULL) return 0;

    int n = 0;
    NodeV *aux = G[v].Adj;
    while (aux != NULL){
        n++;  
        aux = aux->next;
    }
    return n;
}

/*retorna 1 caso todos pares, 2 caso 1 ou 2 impares e 2 caso mais de 2 impares
*/
int IsEulerian(Graph *G){
    int i = 0; 
    int n_odd = 0; 

    for(int i=0; i < G[0].n_vertices; i++){
        if (VerticeDeg(G, i)%2) n_odd++;
    }

    if (n_odd > 2) return 0;
    if (n_odd != 0) return 2;

    return 1;
}

Stack* Hierholzer(Graph *G){
    if (G == NULL) return NULL;
    if (!IsEulerian(G)) return NULL;
    
    Stack *P = CreateStack();
    for (int i = 0; i < G[0].n_vertices; i++){
        HierholzerStack(G[i].Adj, P);
    }

    return P;
}

void HierholzerStack(NodeV *node, Stack *P){

    if (node->next != NULL) HierholzerStack(node->next, P);

    AddElem(P, node->vertex+1);

    return;

}

int IsInAdj(Graph *G, int g_src, int g_dest){
    NodeV *Adj = SearchAdj(G,g_src,g_dest);

    if (Adj == NULL) return 0;
    
    return 1;
}

void PrintGraph(Graph *G){
    NodeV *aux;
    NodeV *aux2;
    
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
