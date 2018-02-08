import sys

MOD  = 1000000007
SAME = 1
DIFFERENT = 0


class Node:
    def __init__(self,i):
        self.i = i
        self.nei = []

    def add_nei(self,nei):
        self.nei.append(nei)

    def num_nei(self):
        return len(self.nei)


def universal_memoization_decorator(computing_func):
    cache = {}
    print(len(cache))
    def wrapped(idx,parent,parent_relation):
        if (idx,parent_relation) not in cache:
            cache[(idx,parent_relation)] = computing_func(idx,parent,parent_relation)
        return cache[(idx,parent_relation)]

    return wrapped


@universal_memoization_decorator
def kingdoms(curr_node,parent,parent_relation):

    idx = curr_node.i
    n = 0
    if idx != 0 and curr_node.num_nei() == 1:
        return 1 if parent_relation == SAME else 0

    if(parent_relation == SAME):
        s = 1
        for nei in curr_node.nei:

            if nei.i == parent:
                continue
            n = kingdoms(nei,idx,SAME)
            n += kingdoms(nei, idx, DIFFERENT)
            s = (s * (n % MOD)) % MOD;
        return s

    else:
        total = 0
        for (current_idx,current_nei) in enumerate(curr_node.nei):
            s = 1
            if current_nei.i == parent:
                continue

            for (other_idx,other_nei) in enumerate(curr_node.nei):
                if other_nei.i == parent:
                    continue
                n = 0
                if other_idx < current_idx:
                    n = kingdoms(other_nei,idx,DIFFERENT)
                elif other_idx == current_idx:
                    n = kingdoms(other_nei, idx, SAME)
                else:
                    n = kingdoms(other_nei, idx, SAME)
                    n += kingdoms(other_nei, idx, DIFFERENT)
                s = (s * (n % MOD)) % MOD;
            total = (total + s) % MOD
        return total


def main(args):

    filename = args[1]

    f = open(filename, 'r')

    n = int(f.readline())
    print("n = %d" % n)
    print("limit = %d" % sys.getrecursionlimit())
    sys.setrecursionlimit(99497)


    nodes = [None] * n

    max_nei = 0
    max_nei_idx = 0
    for i in range(n-1):
        [x, y] = [int(a) for a in f.readline().split()]
        if not nodes[x-1]:
            nodes[x-1] = Node(x-1)


        if not nodes[y-1]:
            nodes[y-1] = Node(y-1)

        nodes[x-1].add_nei(nodes[y-1])
        nodes[y-1].add_nei(nodes[x-1])

        if(nodes[x-1].num_nei() > max_nei):
            max_nei = nodes[x-1].num_nei()
            max_nei_idx = x-1

        if (nodes[y - 1].num_nei() > max_nei):
            max_nei = nodes[y - 1].num_nei()
            max_nei_idx = y - 1


    f.close()
    kingdoms_nr = kingdoms(nodes[max_nei_idx],-1,DIFFERENT)

    print("sum = %d" % ((2*kingdoms_nr)%MOD))


if __name__ == "__main__":
    main(sys.argv)



