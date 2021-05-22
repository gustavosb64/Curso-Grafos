#include <stdio.h>
#include <stdlib.h>
#include "grafos_lista_adjacencias.h"
#include "./Pilha/pilha_encadeada.h"
//#include "../ReadPajek/read_pajek.h"
#include "../ReadPajek/read_pajek.h"

#define READLINE_BUFFER 4096

/*
char *readline(FILE *stream);
void readPajek(Graph *G, FILE *file);
int getNumVertices(FILE *file);
*/

int main(int argc, char *argv[]){

    FILE *file;
    file = fopen("amostra_pajek.txt","r");

    int n_vertices = getNumVertices(file);

    Graph *G;
    G = CreateGraph(n_vertices); 

    readPajek(G, file);
    PrintGraph(G);

    printf("VerticeDeg 4: %d\n", VerticeDeg(G, 3));
    printf("IsEulerian: %d\n", IsEulerian(G));

    Stack *P = Hierholzer(G);
    PrintStack(P);

    FreeGraph(G);
    FreeStack(P);
    fclose(file);

    return 0;
}

/*
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

    fseek(file,20,SEEK_SET);
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

//FUNCAO DE LEITURA DE LINHA
char *readline(FILE *stream) {
    char *string = 0;
    int pos = 0; 

	do{
        if (pos % READLINE_BUFFER == 0) {
            string = (char *) realloc(string, (pos / READLINE_BUFFER + 1) * READLINE_BUFFER);
        }
        string[pos] = (char) fgetc(stream);
    }while(string[pos++] != '\n' && string[pos-1] != ' ' && string[pos-1] != '\r' && !feof(stream));

    string[pos-1] = 0;
    string = (char *) realloc(string, pos);

    return string;
}
*/
