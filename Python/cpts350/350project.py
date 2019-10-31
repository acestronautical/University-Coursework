#!/usr/bin/env python3
from pyeda.inter import *
from graphviz import Source

# note that in order for graphviz to work you need to pip3 install graphviz
# and also sudo apt install graphviz 

def printBDD(bdd):
    Source(bdd.to_dot(), filename="test.gv", format="png").view()


def bin2expstr(binstring, varname):
    exp = ''
    for i in range(len(binstring)):
        if binstring[i] == '1':
            exp += varname
        elif binstring[i] == '0':
            exp += '~' + varname
        exp += str(i) + ' & '
    return exp[:-3]


def pairs2bdd(pairsL):
    edgeExpressions = []
    for p1, p2 in edgePairs:
        ex = bin2expstr(p1, 'x')
        ex += ' & '
        ex += bin2expstr(p2, 'y')
        edgeExpressions.append(expr(ex))

    G = expr2bdd(edgeExpressions[0])
    for x in edgeExpressions:
        G |= expr2bdd(x)
    return G


# main
if __name__ == "__main__":

    # make graph BDD
    edgePairs = []
    for i in range(0, 32):
        for j in range(0, 32):
            if ((i + 3) % 32 == j % 32) or ((i + 8) % 32 == j % 32):
                edgePairs.append((f'{i:05b}', f'{j:05b}'))

    G = pairs2bdd(edgePairs)

    # make primes BDD
    primesExpressions = []
    pList = [3, 5, 7, 11, 13, 17, 19, 23, 29, 31]
    for i in range(0, 32):
        if i in pList:
            primesExpressions.append(expr(bin2expstr(f'{i:05b}', 'p')))

    primes = expr2bdd(primesExpressions[0])
    for p in primesExpressions:
        primes |= expr2bdd(p)

    # get BDD variables
    x0, x1, x2, x3, x4, y0, y1, y2, y3, y4 = G.inputs
    p0, p1, p2, p3, p4 = primes.inputs
    z0, z1, z2, z3, z4 = bddvars('z', 5)

    # starting from a prime BDD
    primeStart = primes.compose({p0: x0, p1: x1, p2: x2, p3: x3, p4: x4})
    P = (primeStart & G)

    # reachable is the bdd of nodes reachable in an even number of steps
    # and starting from a prime node
    r1 = P.compose({y0: z0, y1: z1, y2: z2, y3: z3, y4: z4})
    r2 = G.compose({x0: z0, x1: z1, x2: z2, x3: z3, x4: z4})
    reachable = (r1 & r2).smoothing([z0, z1, z2, z3, z4])

    # two steps in G
    g1 = G.compose({y0: z0, y1: z1, y2: z2, y3: z3, y4: z4})
    g2 = G.compose({x0: z0, x1: z1, x2: z2, x3: z3, x4: z4})
    twosteps = (g1 & g2).smoothing([z0, z1, z2, z3, z4])

    # ends on an even BDD
    evenEnd = expr2bdd(expr(~y4))

    # generate 2 steps, 4 steps, etc... BDD's and OR them with reachable
    curEven = reachable
    # twosteps z -> y
    twosteps = twosteps.compose({x0: z0, x1: z1, x2: z2, x3: z3, x4: z4})
    for i in range(15):
        # temp x -> z
        curEven = curEven.compose({y0: z0, y1: z1, y2: z2, y3: z3, y4: z4})
        curEven = (curEven & twosteps).smoothing([z0, z1, z2, z3, z4])
        temp = (curEven & evenEnd)
        reachable |= temp

    printBDD(reachable)
    # printBDD(primes)

# The resulting BDD is equal to the primes BDD, so in order to reach an even
# node in an even number of steps, the only restriction is that you start from
# an even node, which is what we want. So the property:
# """
# for each node u in [prime], there is a node v in [even] such that u can reach 
# v in even number of steps
# """
# is true for this graph
