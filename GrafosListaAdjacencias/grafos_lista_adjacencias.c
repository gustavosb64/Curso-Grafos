#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "grafos_lista_adjacencias.h"
#include "../EstruturasDeDados/Pilha/pilha_encadeada.h"
#include "../EstruturasDeDados/Fila/fila_encadeada.h"
#include "../EstruturasDeDados/Lista/lista_encadeada.h"
#include "../ReadPajek/read_pajek.h"

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
    int n_odd = 0; 

    for(int i=0; i < G[0].n_vertices; i++){
        if (VerticeDeg(G, i)%2) n_odd++;
    }

    if (n_odd > 2) return 0;
    if (n_odd != 0) return 2;

    return 1;
}

/*
 * ALGORITMO DE HIERHOLZER AINDA EM CONSTRUÇÃO
Stack* Hierholzer(Graph *G){
    if (G == NULL) return NULL;
    if (!IsEulerian(G)){
        printf("Não se trata de um grafo Euleriano.\n");    
        return NULL;
    } 

    List *L_All = CreateList();
    Stack *S_EulerPath = CreateStack();

    for (int i=0; i<G->n_vertices; i++){
        AddLastElem(L_All, i);
    }

    HierholzerStack(G, 0, -1, S_EulerPath);

    for (int i=1; i<G->n_vertices; i++){
        G[i].colour = 'W';
    }

    PrintStack(S_EulerPath);

    return S_EulerPath;
}
*/

/*
 * Sem stack overflow, porém ainda não funcional
void HierholzerStack(Graph *G, int index, int parent_index, Stack *S_EulerPath){
    
    printf("index: %d\tparent: %d\n",index+1,parent_index+1);
    NodeV *aux_node = G[index].Adj;
    while (aux_node != NULL){
        if (aux_node->vertex == parent_index) return;
        if (G[aux_node->vertex].colour != 'B'){
            HierholzerStack(G, aux_node->vertex, index, S_EulerPath);
        }
        aux_node = aux_node->next;
    }

    G[index].colour = 'B';
    AddElemStack(S_EulerPath, index); 
    printf("cheguei\n");

    return;
}
*/

int IsInAdj(Graph *G, int g_src, int g_dest){
    NodeV *Adj = SearchAdj(G,g_src,g_dest);

    if (Adj == NULL) return 0;
    
    return 1;
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

NodeV* BFS (Graph *G, elem e){

    //Lista para nós brancos e pretos e fila para nós cinzas
    List *L_White = CreateList();
    List *L_Black = CreateList();
    Queue *Q_Grey = CreateQueue(); 

    for (int i=1; i<G->n_vertices; i++){
        G[i].colour = 'W';
        AddLastElem(L_White, i);
    }

    AddElemQueue(Q_Grey, 0);
    G[0].colour = 'G';
    G[0].dist = 0;
    NodeV *aux_node;
    int q_index;
    int aux_e;
    while(!IsEmptyQueue(Q_Grey)){ 
        OutQueue(Q_Grey, &q_index);
        aux_node = G[q_index].Adj;
        while (aux_node != NULL){
            printf("aux_node->vertex: %d\tDistance: %d\n", aux_node->vertex, G[q_index].dist);
            if (aux_node->vertex == e){
                FreeList(L_Black);
                FreeList(L_White);
                FreeQueue(Q_Grey);
                printf("Element found. Distance: %d\n", G[q_index].dist + 1);

                return aux_node;
            }
            
            if(G[aux_node->vertex].colour == 'W'){
                AddElemQueue(Q_Grey, aux_node->vertex);
                G[aux_node->vertex].dist = G[q_index].dist + 1;
                G[aux_node->vertex].colour = 'G';
                SearchRemoveElem(L_White, &aux_node->vertex, &aux_e);
            }
            aux_node = aux_node->next;
        }
        AddLastElem(L_Black, q_index);
        G[q_index].colour = 'B';
    }

    FreeList(L_Black);
    FreeList(L_White);
    FreeQueue(Q_Grey);

    printf("Element not found!\n");

    return NULL;
}

void RecursiveDFS(Graph *G, int cur_index, elem e, int *time, int **local_clock, Stack *B_Stack){

    if(G[cur_index].Adj == NULL || G[cur_index].colour != 'W') return;

    (*time)++;
    G[cur_index].colour = 'G';
    local_clock[cur_index][0] = *time;
    
    NodeV* aux_node = G[cur_index].Adj;
    while (aux_node != NULL){
        RecursiveDFS(G, aux_node->vertex, e, time, local_clock, B_Stack);
        aux_node = aux_node->next;
    }

    G[cur_index].colour = 'B';
    AddElemStack(B_Stack, cur_index);
    (*time)++;
    local_clock[cur_index][1] = *time;
    return;
}

Stack* DFS(Graph *G, elem e){

    for(int i=0; i<G->n_vertices; i++){
        G[i].colour = 'W';    
    }

    //file with root
    FILE *fRoot = fopen("../Amostras/ArquivosDFS/Raiz.txt","r");
    if (fRoot == NULL){
        printf("Arquivo não encontrado!\n");
        return NULL;
    }

    //decremented for reading
    char *sRoot = readline(fRoot);
    int root = atoi(sRoot) - 1;
    free(sRoot);
 
    //stack with last visited vertices
    Stack *B_Stack = CreateStack();

    //stores the time each vertex were last visited
    int **local_clock = (int **) malloc(G->n_vertices * sizeof(int*));
    for (int i=0; i<G->n_vertices; i++) local_clock[i] = (int *) malloc(2 * sizeof(int));
    int time;

    RecursiveDFS(G, root, e, &time, local_clock, B_Stack);

    /* Print the B_Stack and the time each vertex had been found
    PrintStack(B_Stack);
    for (int i=0; i<G->n_vertices; i++)
        printf("%d: %d\t%d\n",i+1,local_clock[i][0],local_clock[i][1]);
    */


    fclose(fRoot);
    FreeStack(B_Stack);
    for (int i=0; i<G->n_vertices; i++) 
        free(local_clock[i]);
    free(local_clock);

    return NULL;
}
