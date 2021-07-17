from graph import *

filename = input()
G = Graph(filename)

dist_arrays = []
n_max = 0
for i in range (G.n_vertices):
    dist_arrays.append(G.dijkstra(i))
    for j in range(len(dist_arrays[i])):
        if n_max < len(str(dist_arrays[i][j])):
            n_max = len(str(dist_arrays[i][j]))

for i in range (len(dist_arrays)):
    string = ""
    for j in range (len(dist_arrays[i])):
        string = str(dist_arrays[i][j]).rjust(n_max)
        print(string, end=" ")
    print()
