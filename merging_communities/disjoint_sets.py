#only roots can have the size of the set

class Node:
    def __init__(self,i):
        self.parent = i
        self.rank = 0
        self.size = 1

class DisjointSets:
    def __init__(self,sz):
        self.sets = []
        for i in range(0,sz):
            self.sets.append(Node(i))

    def find(self,a):
        if self.sets[a].parent != a:
            self.sets[a].parent = self.find(self.sets[a].parent)
        return self.sets[a].parent

    def size(self,a):
        return self.sets[self.find(a)].size

    def union(self,x,y):
        xroot = self.find(x)
        yroot = self.find(y)

        if xroot == yroot:
            return

        #we add the shorter tree as the child of the higher tree,
        #this way the ranks won't change

        if self.sets[xroot].rank < self.sets[yroot].rank:
            self.sets[xroot].parent = yroot
            self.sets[yroot].size += self.sets[xroot].size
        elif self.sets[xroot].rank > self.sets[yroot].rank:
            self.sets[yroot].parent = xroot
            self.sets[xroot].size += self.sets[yroot].size
        else:
            self.sets[yroot].parent = xroot
            #this is the only case where the rank of is incremented -
            #you add it a child with the same size
            self.sets[xroot].rank += 1
            self.sets[xroot].size += self.sets[yroot].size
