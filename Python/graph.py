from enum import Enum
import numpy as np

class Color(Enum):
    WHITE = 1
    BLACK = 2
    GRAY = 3

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
                n = NodeV(i, Color.WHITE)
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

    def getNumVertices(self):
        return self.n_vertices

    def setNumVertices(self, n_vertices):
        self.n_vertices = n_vertices
        return


    def isEmpty(self):
        if (len(self.vertices) == 0):
            return True
        return False


    #Checks whether vertex g_dest already has an edge with vertex g_src
    # If it doesn't, insert new edge between them
    def insertEdge(self, g_src, g_dest, weight):

        newEdge = NodeEdge(g_dest, weight) 
        self.vertices[g_src].AdjList.append(newEdge)

        return

    #Searches in g_src edge between g_dest and removes it
    def removeEdge(self, g_src, g_dest):

        for edge in self.vertices[g_src].AdjList:
            if (edge.vertex == g_dest): 
                self.vertices[g_src].AdjList.remove(edge)
                return
        return

    #Get the number of vertices adjacents to vertex v
    def getVertexDegree(self, v):
        return len(self.vertices[v].AdjList)
        
    def isEulerian(self):
        n_odd = 0

        for i in range(self.n_vertices):
            if (self.getVertexDegree(i)%2):
                n_odd += 1

        return True if (n_odd == 0) else False

    #Depth First Search
    #Counts the number of components and how many vertices there are in each of them
    def recursiveDFS(self, cur_index, S_Black, L_White):

        if (self.vertices[cur_index].color != Color.WHITE):
            return

        L_White.remove(cur_index)

        cur_vertex = self.vertices[cur_index]
        if(len(cur_vertex.AdjList) > 0):

            cur_vertex.color = Color.GRAY

            for node in cur_vertex.AdjList:
                self.recursiveDFS(node.vertex, S_Black, L_White)

        cur_vertex.color = Color.BLACK
        S_Black.append(cur_index)


    def DFS(self):
        
        L_White = []
        S_Black = []

        for i in range(0, self.n_vertices):
            self.vertices[i].color = Color.WHITE
            L_White.append(i)

        n_vertices_component = []

        while(len(L_White) > 0):
            root = L_White[0]
            self.recursiveDFS(root, S_Black, L_White)

            n_vertices_component.append(len(S_Black))

    #Breadth First Search
    #When element is found, it is returned
    def BFS (self, elem):
        L_White = []
        L_Black = []
        Q_Gray = []
        
        for i in range(1, self.n_vertices):
            self.vertices[i].color = Color.WHITE
            L_White.append(i)

        Q_Gray.append(0)
        self.vertices[0].color = Color.GRAY

        while(len(Q_Gray) != 0):
            q_index = Q_Gray.pop(0)
            adj_list = self.vertices[q_index].AdjList

            for node in adj_list:

                if(node.vertex == elem):
                    print("Element found.")
                    return node

                if(self.vertices[node.vertex].color == Color.WHITE):
                    self.vertices[node.vertex].color = Color.GRAY 
                    Q_Gray.append(node.vertex)
                    L_White.remove(node.vertex)
                    
            L_Black.append(q_index)
            self.vertices[q_index].color = Color.BLACK

        print("Element not found!")
        return

    def printDist(self):
        for vertex in self.vertices:
            for edge in vertex.AdjList:
                print(edge.distance)

    #Dijkstra Algorithm
    #Search for the shortest path to each vertex
    def dijkstra(self, idx_start):

        L_White = []
        S_Black = []

        for i in range(0, self.n_vertices):
            self.vertices[i].color = Color.WHITE
            self.vertices[i].distance = np.inf
            L_White.append(self.vertices[i])
        
        cur_idx = idx_start
        cur_vertex = self.vertices[cur_idx]
        cur_vertex.distance = 0

        while(len(L_White) > 0):

            #print("cur_vertex: "+str(cur_vertex.vertex+1))

            if (len(cur_vertex.AdjList) > 0):
                next_vertex = None
                next_dist = np.inf

            for node in cur_vertex.AdjList:
                node_vertex = self.vertices[node.vertex]
                cur_distance = cur_vertex.distance + node.weight

                if (node_vertex.color == Color.WHITE):
                    if (cur_distance < node_vertex.distance):
                        node_vertex.distance = cur_distance
                
            if (cur_vertex.color == Color.WHITE):
                #print("remove: "+str(cur_vertex.vertex))
                L_White.remove(cur_vertex)
                S_Black.append(cur_vertex)
                cur_vertex.color = Color.BLACK

            L_White = sorted(L_White, key=lambda vertex: vertex.distance)
            """
            for vertex in L_White:
                print("v: "+str(vertex.vertex+1)+" v_dist: "+str(vertex.distance))
            print("------------------------------")
            """

            if(len(L_White) > 0):
                cur_vertex = L_White[0]

        array_distance = []
        for vertex in self.vertices:
            array_distance.append(vertex.distance)

        print(array_distance)
"""
newlist = sorted(cArray, key=lambda classe: classe.x)
"""

            
