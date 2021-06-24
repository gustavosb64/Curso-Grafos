all:
	gcc -g -o main main.c trabalho03_DFS.c ./grafos_lista_adjacencias.c ./EstruturasDeDados/Pilha/pilha_encadeada.c ./EstruturasDeDados/Fila/fila_encadeada.c ./EstruturasDeDados/Lista/lista_encadeada.c ./ReadPajek/read_pajek.c 

run:
	./main
debug:
	valgrind --track-origins=yes --leak-check=full --show-leak-kinds=all ./main
