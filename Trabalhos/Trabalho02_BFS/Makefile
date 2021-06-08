all:
	gcc -Wall -Wpedantic -g -o main main.c trabalho02_BFS.c ../../GrafosListaAdjacencias/grafos_lista_adjacencias.c ../../EstruturasDeDados/Pilha/pilha_encadeada.c ../../EstruturasDeDados/Fila/fila_encadeada.c ../../EstruturasDeDados/Lista/lista_encadeada.c ../../ReadPajek/read_pajek.c 

run:
	./main
debug:
	valgrind --leak-check=full --show-leak-kinds=all ./main
