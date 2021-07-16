from graph import *

"""
G = Graph(5)

print(G.getNumVertices())

print(G)

print(G.isEmpty())

G.insertEdge(1, 2, 1)
G.insertEdge(1, 3, 1)
G.insertEdge(3, 2, 1)
G.insertEdge(4, 1, 1)
G.insertEdge(2, 4, 1)
G.insertEdge(0, 3, 1)
print(G)

print("------------")

G.removeEdge(4, 1)

print(G)

print(G.getVertexDegree(1))
print(G.getVertexDegree(4))
print(G.getVertexDegree(0))

print(G.isEulerian())

G2 = Graph()
print(G2.getNumVertices())

G.BFS(3)

print("n_vertices: "+str(G.n_vertices))
"""

#filename = "../Amostras/amostra_pajek.txt"
filename = "../Trabalhos/Trabalho04_Dijkstra/case1.pajek"

G = Graph(filename)
print(G)
print("Is Eulerian? "+str(G.isEulerian()))
G.BFS(3)
G.DFS()
G.dijkstra()
