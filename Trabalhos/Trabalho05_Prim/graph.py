from enum import Enum
import numpy as np

class NodeEdge:

    def __init__(self, vertex, weight):
        self.vertex = vertex
        self.weight = weight

class NodeV:

    def __init__(self, vertex, color):
        self.vertex = vertex
        self.color = color
        self.AdjList = []
        self.distance = np.inf

class Graph:

    def __init__(self, filename):

        self.vertices = []
        self.n_vertices = 0

        #read edges for undirected graph
        def readEdges(string):
            for line in string:
                vertices_data = line.split()
                if (len(vertices_data) < 3):
                    weight = 1
                else:
                    weight = int(vertices_data[2])
                self.insertEdge(int(vertices_data[0])-1, int(vertices_data[1])-1, weight)
                self.insertEdge(int(vertices_data[1])-1, int(vertices_data[0])-1, weight)

        #read edges for directed graph
        def readArcs(string):
            for line in string:
                vertices_data = line.split()
                if (len(vertices_data) < 3):
                    weight = 1
                else:
                    weight = int(vertices_data[2])
                self.insertEdge(int(vertices_data[0])-1, int(vertices_data[1])-1, weight)

        with open(filename, "r") as file:
            string = file.readlines()

            #Reading number of vertices
            line = string[0].split()
            self.n_vertices = int(line[1])

            for i in range (self.n_vertices):
                n = NodeV(i, 'W')
                self.vertices.append(n)

            line = string[1]
            if("Edges" in line):
                readEdges(string[2:])
            elif("Arcs" in line):
                readArcs(string[2:])

    def __str__(self):
        string = ""

        for i in range(0, self.n_vertices):
            string = string + "vertex:"+str(i+1) + "\n"
            for edge in self.vertices[i].AdjList:
                string = string + "  |-> "+str(edge.vertex+1)+"  "+str(edge.weight)
                string = string + "\n"

        return string

    """
    Checks whether graph is empty
    """
    def isEmpty(self):
        if (len(self.vertices) == 0):
            return True
        return False

    """
    Checks whether vertex g_dest already has an edge with vertex g_src
        If it doesn't, insert new edge between them
    """
    def insertEdge(self, g_src, g_dest, weight):

        newEdge = NodeEdge(g_dest, weight) 
        self.vertices[g_src].AdjList.append(newEdge)
        return

    """
    Searches in g_src edge between g_dest and removes it
    """
    def removeEdge(self, g_src, g_dest):

        for edge in self.vertices[g_src].AdjList:
            if (edge.vertex == g_dest): 
                self.vertices[g_src].AdjList.remove(edge)
                return
        return

    """
    Prim's Algorithm
        Search for the minimum spanning tree
    """
    def prim(self):

        L_White = []
        L_Black = []
        for i in range(0, self.n_vertices):
            self.vertices[i].color = 'W'
            self.vertices[i].distance = np.inf
            L_White.append(self.vertices[i])

        #setting start for 0 
        cur_idx = 0
        self.vertices[cur_idx].distance = 0

        sum_distance = 0
        while(len(L_White) > 0):

            #sort L_White according to lowest distance
            L_White = sorted(L_White, key=lambda vertex: vertex.distance)
            cur_vertex = L_White[0]

            for node in cur_vertex.AdjList:
                node_vertex = self.vertices[node.vertex]

                if (node_vertex.color == 'W' and node.weight < node_vertex.distance):
                    node_vertex.distance = node.weight
                
            if (cur_vertex.color == 'W'):
                L_White.remove(cur_vertex)
                cur_vertex.color = 'B'
                L_Black.append(cur_vertex)
                sum_distance += cur_vertex.distance

        print(sum_distance)

