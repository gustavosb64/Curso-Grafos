import numpy as np

class NodeEdge:

    def __init__(self, vertex, weight):
        self.vertex = vertex
        self.weight = weight

class NodeV:

    def __init__(self, vertex, color):
        self.vertex = vertex
        self.color = color
        self.known_parents = 0
        self.AdjList = []
        self.distance = np.inf
        self.distance2 = np.inf

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
    Checks whether vertex g_dest already has an edge with vertex g_src
        If it doesn't, insert new edge between them
    """
    def insertEdge(self, g_src, g_dest, weight):

        newEdge = NodeEdge(g_dest, weight) 
        self.vertices[g_src].AdjList.append(newEdge)
        return

    """
    Searches in vertex g_src edge between it and g_dest and removes it
    """
    def removeEdge(self, g_src, g_dest):

        for edge in self.vertices[g_src].AdjList:
            if (edge.vertex == g_dest): 
                self.vertices[g_src].AdjList.remove(edge)
                return
        return

    """
    Depth First Search
        Returns:
            Number of source vertices
            Number of sink vertices
            List with all sink vertices whose both parents descend from vertex 1
    """
    def DFS(self):
        
        def recursiveDFS(cur_index, S_Black, L_White, n_sink_vertices):

            cur_vertex = self.vertices[cur_index]

            if (cur_vertex.color != 'W'):
                if (len(cur_vertex.AdjList) == 0 and cur_vertex.known_parents > 1):
                    S_Black.append(cur_index)
                return n_sink_vertices

            L_White.remove(cur_index)

            if(len(cur_vertex.AdjList) > 0):

                cur_vertex.color = 'G'

                for node in cur_vertex.AdjList:
                    self.vertices[node.vertex].known_parents += 1
                    n_sink_vertices = recursiveDFS(node.vertex, S_Black, L_White, n_sink_vertices)
            else:
                n_sink_vertices += 1

            cur_vertex.color = 'B'

            return n_sink_vertices

        L_White = [] #List with non visited vertices
        S_Black = [] #List (stack) with visited vertices. Used only for sink vertices 

        for i in range(0, self.n_vertices):
            self.vertices[i].color = 'W'
            L_White.append(i)

        n_source_vertices = 0
        n_sink_vertices = 0
        L_DescendFirstVertex = [] #List with sink vertices whose both parents descend from vertex 1

        #Get all necessary data from vertex 1 before checking other lineages
        root = L_White[0]
        n_sink_vertices = recursiveDFS(root, L_DescendFirstVertex, L_White, n_sink_vertices)
        n_source_vertices += 1
        L_DescendFirstVertex = sorted(L_DescendFirstVertex)

        while(len(L_White) > 0):
            root = L_White[0]
            n_sink_vertices = recursiveDFS(root, S_Black, L_White, n_sink_vertices)
            n_source_vertices += 1 

        return n_source_vertices, n_sink_vertices, L_DescendFirstVertex

    """
    Breadth First Search
        Returns:
            List with all elements in L_DescendFirstVertex sorted by their distance to vertex 1
    """
    def BFS (self, L_DescendFirstVertex):
        L_White = []
        Q_Gray = []
        L_Black = [] #List with visited vertices
                        #Used only to store vertices also in L_DescendFirstVertex
        
        for i in range(1, self.n_vertices):
            self.vertices[i].color = 'W'
            L_White.append(self.vertices[i])

        Q_Gray.append(self.vertices[0])
        self.vertices[0].color = 'G'
        self.vertices[0].distance = 0

        while(len(Q_Gray) != 0):
            q_vertex = Q_Gray.pop(0)

            for node in q_vertex.AdjList:
                cur_vertex = self.vertices[node.vertex]

                #if minimum distance is already found, stores other distance in distance2
                if (cur_vertex.distance == np.inf):
                    cur_vertex.distance = q_vertex.distance + 1 
                else:
                    cur_vertex.distance2 = q_vertex.distance + 1 

                if(cur_vertex.color == 'W'):
                    cur_vertex.color = 'G' 
                    Q_Gray.append(cur_vertex)
                    L_White.remove(cur_vertex)
                    
            #append to L_Black only if q_vertex is descendant from vertex 1
            if (q_vertex.vertex in L_DescendFirstVertex):
                L_Black.append(q_vertex)
            q_vertex.color = 'B'

        #Sum the distances from both parents to each vertex in L_Black
        for v in L_Black:
            v.distance += v.distance2

        #sort according to their distance to vertex 1
        L_Black = sorted(L_Black, key=lambda vertex: vertex.distance)

        return L_Black

class main:

    filename = str(input())

    if (filename == "case.pajek"):
        filename = "case3.pajek"

    G = Graph(filename)

    n_source_vertices, n_sink_vertices, L_DescendFirstVertex = G.DFS()
    L_Black = G.BFS(L_DescendFirstVertex)

    #PART1: Number of source vertices:
    print("PART1")
    print(n_source_vertices)
    print("----------------")

    #PART2: Number of sink vertices:
    print("PART2")
    print(n_sink_vertices)
    print("----------------")


    #PART3: Number of sink vertices descendent from vertex 1:
    print("PART3")
    for i in L_DescendFirstVertex:
        print(i+1)
    print("----------------")

    #PART4: Shortest distance from L_DescendFirstVertex
    #Since L_Black has all elements from L_DescendFirstVertex sorted by their distance,
        #the shortest distance is the first element's 
    shortest_dist = L_Black[0].distance
    output_shortest_dist = []
    for v in L_Black:
        if v.distance != shortest_dist:
            break
        output_shortest_dist.append(v.vertex+1)

    print("PART4")
    #sorting them by vertex number before printing
    output_shortest_dist = sorted(output_shortest_dist)
    for i in output_shortest_dist:
        print(i)
    print("----------------")
