all:
	gcc -g -o main main.c grafos_lista_adjacencias.c Pilha/pilha_encadeada.c ../ReadPajek/read_pajek.c

comp:
	gcc -g -o main main.c grafos_lista_adjacencias.c Pilha/pilha_encadeada.c

comp2:
	gcc -g -o main main.c grafos_lista_adjacencias.c Pilha/pilha_encadeada.c ReadPajek/read_pajek.c

run:
	valgrind ./main
run_v:
	valgrind --leak-check=full --show-leak-kinds=all ./main
