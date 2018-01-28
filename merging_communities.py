import re
import sys

set_dict = {}

def union(x,y):
    m = set()
    for z in [x,y]:
        for c in set_dict[z]:
            m.add(c)
            set_dict[c] = m


def size(x):
    print(len(set_dict[x]))


l = sys.stdin.readline()

N = int(re.compile("^([0-9]+) .*$").match(l).group(1))
S = int(re.compile("^.* ([0-9]+)$").match(l).group(1))

#print("N = %d S = %d" % (N,S))

set_dict = dict([(i, set([i])) for i in range(1,N+1)])

nregex = re.compile("^M ([0-9]+) ([0-9]+)$")

for line in sys.stdin:
    if line.startswith('Q'):
        x = int(re.compile("^.* ([0-9]+)$").match(line).group(1))
        #print("x = %d" % x)
        size(x)
    else:
        m = nregex.match(line)
        y = int(m.group(1))
        x = int(m.group(2))
        #print("x = %d y = %d" % (x,y))
        union(x,y)
