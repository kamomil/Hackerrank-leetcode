import re
import sys
import disjoint_sets

#https://www.hackerrank.com/challenges/merging-communities/problem

l = sys.stdin.readline()

N = int(re.compile("^([0-9]+) .*$").match(l).group(1))
S = int(re.compile("^.* ([0-9]+)$").match(l).group(1))

sets = DisjointSets(N)

mregex = re.compile("^M ([0-9]+) ([0-9]+)$")
qregex = re.compile("^Q ([0-9]+)$")

for line in sys.stdin:
    if line.startswith('Q'):
        x = int(qregex.match(line).group(1))
        print(sets.size(x-1))
    else:
        m = mregex.match(line)
        y = int(m.group(1))
        x = int(m.group(2))
        sets.union(x-1,y-1)
