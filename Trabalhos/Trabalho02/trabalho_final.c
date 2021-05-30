#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define READLINE_BUFFER 4096
#define INFINITY INT_MAX/2
#define READLINE_BUFFER 4096

typedef int elem;
typedef struct node_q_ NodeQ;
typedef struct queue_ Queue;
typedef struct node_l_ NodeL;
typedef struct list_ List;
typedef struct node_v_ NodeV;
typedef struct grafo_ Graph;

struct node_q_{
    elem val;
    struct node_q_ *next;
};

struct queue_{
    NodeQ *first;
    NodeQ *last;
    int n_elem;
};

Queue* CreateQueue(){
    Queue *queue = (Queue *) malloc(sizeof(Queue)); 
    
    queue->first = NULL; 
    queue->last = queue->first; 

    queue->n_elem = 0; 

    return queue;
}

int IsEmptyQueue(Queue *queue){
    if (queue->n_elem == 0) return 1;
    else return 0;
}

int AddElemQueue(Queue *queue, elem e){
    NodeQ *aux_node = (NodeQ *) malloc(sizeof(NodeQ));
    if (aux_node == NULL) return 1;

    if (IsEmptyQueue(queue)){
        queue->first = aux_node;
    }
    else {
        queue->last->next = aux_node; 
    }

    queue->last = aux_node;

    queue->last->val = e;
    queue->last->next = NULL;

    queue->n_elem++;

    return 0;
}

int OutQueue(Queue *queue, elem *e){

    if(IsEmptyQueue(queue)) return 1;

    *e = queue->first->val;
    
    NodeQ *aux_node = queue->first->next;

    free(queue->first);
    queue->first = aux_node;

    queue->n_elem--;

    return 0;
}

NodeQ* SearchElemQueue(Queue *queue, elem e, int *error){

    if(IsEmptyQueue(queue)){
        *error = 1;
        return NULL;
    }

    NodeQ *dest_node;
    dest_node = queue->first;

    while (dest_node != NULL){
        if (dest_node->val == e){
            return dest_node;
        }
        dest_node = dest_node->next;
    }
    
    *error = 2;
    return NULL;
}

int PrintQueue(Queue *queue){

    if(IsEmptyQueue(queue)) return 1;
    
    NodeQ *aux_node = queue->first;
    
    while(aux_node!=NULL){
        printf("%d\n",aux_node->val+1);
        aux_node = aux_node->next;
    }

    return 0;
}

int FreeQueue(Queue *queue){

    if(IsEmptyQueue(queue)){
        free(queue->first);
        free(queue);
        return 1;
    }
    
    NodeQ *aux_node = queue->first;
    NodeQ *aux_node2;
    while(aux_node != NULL){
        aux_node2 = aux_node;
        aux_node = aux_node->next;
        free(aux_node2);
    }
    free(aux_node);
    free(queue);

    return 0;
}

struct node_l_{
    elem val;
    struct node_l_ *next;
    struct node_l_ *prev;
};

struct list_{
    NodeL *first;
    NodeL *last;
    int n_elem;
};

List* CreateList(){
    List *list = (List *) malloc(sizeof(List)); 
    if (list == NULL){
        printf("CreateList FAILED: Memory is full.\n");
        return NULL;
    }
    
    list->first = NULL; 
    list->last = list->first; 

    list->n_elem = 0; 

    return list;
}

int IsEmptyList(List *list){
    if (list->n_elem == 0) return 1;
    else return 0;
}

int AddLastElem(List *list, elem e){
    NodeL *aux_node = (NodeL *) malloc(sizeof(NodeL));
    if (aux_node == NULL) return 1;

    if (IsEmptyList(list)){
        list->first = aux_node;
        list->first->prev = NULL;
    }
    else {
        list->last->next = aux_node; 
        aux_node->prev = list->last;
    }

    list->last = aux_node;

    list->last->val = e;
    list->last->next = NULL;

    list->n_elem++;

    return 0;
}

int AddFirstElem(List *list, elem e){
    NodeL *aux_node = (NodeL *) malloc(sizeof(NodeL));
    if (aux_node == NULL) return 1;

    if (IsEmptyList(list)){
        list->first = aux_node;
        list->first->prev = NULL;
    }
    else {
        list->first->prev = aux_node; 
        aux_node->next = list->first;
    }

    list->first = aux_node;

    list->first->val = e;
    list->first->prev = NULL;

    list->n_elem++;
    return 0;
}

int AddMiddleElem(List *list, elem e, int index){

    if (index == 0){
        if (AddFirstElem(list, e)) return 1;
        return 0;
    }

    if (index == (list->n_elem - 1)){
        if (AddLastElem(list, e)) return 1;
        return 0;
    }

    NodeL *node = (NodeL *) malloc(sizeof(NodeL));
    if (node == NULL) return 1;

    NodeL *aux = list->first;
    int i=1;
    while (i < index){
        aux = aux->next;
        i++;
    }

    node->next = aux->next;
    aux->next = node;
    node->prev = aux;

    node->val = e;

    return 0;
}

int RemoveLastElem(List *list, elem *e){

    if(IsEmptyList(list)) return 1;

    *e = list->last->val;
    
    NodeL *aux_node = list->last->prev;

    if (aux_node != NULL)
        aux_node->next = NULL; 

    free(list->last);
    list->last = aux_node;

    list->n_elem--;

    return 0;
}

int RemoveFirstElem(List *list, elem *e){

    if(IsEmptyList(list)) return 1;

    *e = list->first->val;
    
    NodeL *aux_node = list->first->next;

    if (aux_node != NULL)
        aux_node->prev = NULL; 

    free(list->first);
    list->first = aux_node;

    list->n_elem--;

    return 0;
}

int RemoveOddEven(List *list, elem *e){
    
    if(IsEmptyList(list)) return 1;

    if((list->n_elem)%2) RemoveFirstElem(list, e);
    else RemoveLastElem(list, e);

    return 0;
}

int InList(List *list, elem e){

    if(IsEmptyList(list)) return -1;

    AddLastElem(list, e);

    NodeL *node = list->first;
    while (node->val != e)
        node = node->next;

    int check = 1;
    if (node->next == NULL) check = 0;
    
    RemoveLastElem(list, &e);

    return check;
}

NodeL* SearchElemList(List *list, elem e, int *error, int *index){

    if(IsEmptyList(list)){
        *error = 1;
        return NULL;
    }

    NodeL *dest_node;
    dest_node = list->first;
    *index = 0;

    while (dest_node != NULL){
        if (dest_node->val == e) return dest_node;
        dest_node = dest_node->next;
        *index = *index+1;
    }
    
    *error = 2;
    return NULL;
}

int RemoveMiddleElem(NodeL *node, elem *e){

    if(node == NULL) return 1;
    if (node->prev == NULL) return 2;
    if (node->next == NULL) return 3;

    node->prev->next = node->next;    
    node->next->prev = node->prev;
    
    node->next = NULL;
    node->prev = NULL;
    *e = node->val;

    free(node); 

    return 0;
}

int IndexRemoveElem(List *list, elem *e, int index){

    if(IsEmptyList(list)) return 1;
    if (index > list->n_elem) return 2;
    if (index < 0) return 3;
    
    if (index == 0){
        if (RemoveFirstElem(list, e)) return 1;
        return 0;
    }

    if (index == (list->n_elem - 1)){
        if (RemoveLastElem(list, e)) return 1;
        return 0;
    }

    NodeL *aux = list->first;
    int i=1;
    while (i <= index){
        aux = aux->next;
        i++;
    }
   
    RemoveMiddleElem(aux, e);
    list->n_elem--;

    return 0;
}

int SearchRemoveElem(List *list, elem *e, elem *dest_e){

    if(IsEmptyList(list)) return 1;

    NodeL *dest_node;
    int error = 0;
    int index = 0;

    dest_node = SearchElemList(list, *e, &error, &index);
    switch (error){
        case 1: 
            return 1;
        case 2:
            printf("Element not found!\n");
            free(dest_node);
            return 0;
    }

    if (index == 0){
        if (RemoveFirstElem(list, dest_e)) return 1;
    }
    else if (index == (list->n_elem-1)){
        if (RemoveLastElem(list, dest_e)) return 1;
    }
    else{
        RemoveMiddleElem(dest_node, dest_e);
        list->n_elem--;
    }

    return 0;
}

int PrintList(List *list){

    if(IsEmptyList(list)) return 1;
    
    NodeL *aux_node = list->first;
    
    while(aux_node!=NULL){
        printf("%d\n",aux_node->val+1);
        aux_node = aux_node->next;
    }

    return 0;
}

int FreeList(List *list){
    
    if(IsEmptyList(list)){
        free(list->first); 
        free(list);
        return 1;
    }

    NodeL *aux_node = list->first;
    NodeL *aux_node2;
    while(aux_node!=NULL){
        aux_node2 = aux_node;
        aux_node = aux_node->next;
        free(aux_node2);
    }
    free(aux_node);
    free(list);

    return 0;
}

struct node_v_{
    int vertex;
    int value;
    struct node_v_ *next;
    struct node_v_ *prev;
};

struct grafo_{
    NodeV *Adj;
    char colour; //W -> white; B -> black; G -> grey
    int n_vertices;
    int dist;
};

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

//FUNCAO DE LEITURA DE LINHA
char *readline(FILE *stream) {
    char *string = 0;
    int pos = 0; 
	do{
        if (pos % READLINE_BUFFER == 0) {
            string = (char *) realloc(string, (pos / READLINE_BUFFER + 1) * READLINE_BUFFER);
        }
        string[pos] = (char) fgetc(stream);
    }while(string[pos++] != '\n' && string[pos-1] != '\r' && string[pos-1] != ' ' && !feof(stream));

    if (string[pos-1] == '\r'){
        fseek(stream,1,SEEK_CUR);
    }
    string[pos-1] = 0;
    string = (char *) realloc(string, pos);

    return string;
}

int getNumVertices(FILE *file){

    int n_vertices;
    char *str_vertices;
    fseek(file,10,SEEK_SET);

    str_vertices = readline(file);
    n_vertices = atoi(str_vertices);
    free(str_vertices);

    return n_vertices;
}

void readPajek(Graph *G, FILE *file){

    fseek(file,8,SEEK_CUR);
    int Mi, Mj;
    char *str1, *str2;
    while(!feof(file)){
    
        str1 = readline(file);
        Mi = atoi(str1);

        str2 = readline(file);
        Mj = atoi(str2);
        
        free(str1);
        free(str2);
        if (Mi == 0 || Mj == 0) break;

        Insert(G, Mi-1, Mj-1, 1);
        Insert(G, Mj-1, Mi-1, 1);
    }

    return;
}

int main(int argc, char *argv[]){

    char *string;
    string = readline(stdin);

    FILE *file;
    file = fopen(string,"r");

    int n_vertices = getNumVertices(file);

    Graph *G;
    G = CreateGraph(n_vertices); 

    readPajek(G, file);

    PrintBFS(G);

    FreeGraph(G);
    fclose(file);
    free(string);

    return 0;
}
