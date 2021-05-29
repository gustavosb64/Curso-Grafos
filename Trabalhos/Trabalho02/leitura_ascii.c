#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]){
    FILE *file = fopen("grafo1.pajek","r");

    char c;
    do{
        fread(&c, sizeof(char), 1, file);
        printf("%d ",c); 
    }while(!feof(file));

    return 0;
}
