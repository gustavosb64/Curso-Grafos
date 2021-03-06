#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../GrafosListaAdjacencias/grafos_lista_adjacencias.h"

#define READLINE_BUFFER 4096

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

    char* string = readline(file);
    int directed;
    if (!strcmp(string, "*Arcs")) directed = 0;
    else directed = 1;

    int Mi, Mj;
    char *str1, *str2;
    while(!feof(file)){

        str1 = readline(file);
        if (str1 == NULL){
            free(str1); 
            break;
        }
        Mi = atoi(str1);

        str2 = readline(file);
        if (str2 == NULL){
            free(str2); 
            break;
        }
        Mj = atoi(str2);
        
        free(str1);
        free(str2);
        if (Mi == 0 || Mj == 0) break;

        Insert(G, Mi-1, Mj-1, 1);
        if (directed) Insert(G, Mj-1, Mi-1, 1);
    }

    free(string);

    return;
}
