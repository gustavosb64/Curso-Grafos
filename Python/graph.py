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

    def __init__(self, n_vertices):
        self.n_vertices = n_vertices
        self.vertices = []
        for i in range (n_vertices):
            n = NodeV(i, 'W')
            self.vertices.append(n)
    
    def __str__(self):
        string = ""

        for i in range(0, self.n_vertices):
            string = string + "vertex:"+str(i) + "\n"
            for edge in self.vertices[i].AdjList:
                string = string + "  |-> "+str(edge.vertex)
                string = string + "\n"

        return string


    def isEmpty(self):
        if (self.vertices == None):
            return True
        return False

    """Checks whether vertex g_dest already has an edge with vertex g_src
        If it doesn't, insert new edge between them
    """
    def insertEdge(self, g_src, g_dest, weight):
        
        """
        for node in self.vertices[g_src].AdjList:
            if (node.vertex != None and node.vertex == g_dest):
                return
        """ 

        newEdge = NodeEdge(g_dest, weight) 
        self.vertices[g_src].AdjList.append(newEdge)

        return
