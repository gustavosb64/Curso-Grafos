from enum import Enum

class Color(Enum):
    WHITE = 1
    BLACK = 2
    GRAY = 3

class Pajek:

    def __init__(self, filename):
        self.filename = filename

class NodeEdge:

    def __init__(self, vertex, weight):
        self.vertex = vertex
        self.weight = weight

class NodeV:

    def __init__(self, vertex, color):
        self.vertex = vertex
        self.color = color
        self.AdjList = []

class Graph:

    def __init__(self, n_vertices=0):
        self.n_vertices = n_vertices
        self.vertices = []
        for i in range (n_vertices):
            n = NodeV(i, Color.WHITE)
            self.vertices.append(n)
    
    def __str__(self):
        string = ""

        for i in range(0, self.n_vertices):
            string = string + "vertex:"+str(i) + "\n"
            for edge in self.vertices[i].AdjList:
                string = string + "  |-> "+str(edge.vertex)
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
                    print(L_White)
                    print(L_Black)

                    print("Element found.")
                    return node

                if(G.vertices[node.vertex].color == Color.WHITE):
                    G.vertices[node.vertex].color = Color.GRAY
                    Q_Gray.append(node.vertex)
                    L_White.remove(node.vertex)
                    
            L_Black.append(q_index)
            G.vertices[q_index].color = Color.BLACK

        print("Element not found!")
        return

    #Depth First Search
    #Counts the number of components and how many vertices there are in each of them
    def DFS(self):
        
        L_White = []
        S_Black = []

        for i in range(1, self.n_vertices):
            self.vertices[i].color = Color.WHITE
            L_White.append(i)

        n_vertices_component = []

        while(len(L_White) > 0):
            root = L_White.pop(0)

            recursiveDFS(root, S_Black, L_White)

            n_vertices_component.append(len(S_Black))

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
