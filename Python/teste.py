class teste1:

    def __init__(self):
        self.n = 8

    def recursiveMethod(self, lista):

        if (len(lista) > 5):
            lista.pop(0)
            return self.recursiveMethod(lista)

        return


    def method(self):

        lista = []
        for i in range(10):
            lista.append(i)

        print(lista)

        self.recursiveMethod(lista)

        print(lista)
