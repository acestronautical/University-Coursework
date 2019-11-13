#!/usr/bin/env python3
from pyeda.inter import *
from graphviz import Source

# Author: Ace Cassidy

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

    return G


# main
if __name__ == "__main__":

    # G is BDD for: edges of G
    edgePairs = []
    for i in range(0, 32):
        for j in range(0, 32):
            if ((i + 3) % 32 == j % 32) or ((i + 8) % 32 == j % 32):
                edgePairs.append((f'{i:05b}', f'{j:05b}'))

    edgeExpressions = []
    for p1, p2 in edgePairs:
        ex = bin2expstr(p1, 'x')
        ex += ' & '
        ex += bin2expstr(p2, 'y')
        edgeExpressions.append(expr(ex))

    G = expr2bdd(edgeExpressions[0])
    for x in edgeExpressions:
        G |= expr2bdd(x)

    # primes is BDD for: is a prime number (not 2 tho)
    primesExpressions = []
    pList = [3, 5, 7, 11, 13, 17, 19, 23, 29, 31]
    for i in range(0, 32):
        if i in pList:
            primesExpressions.append(expr(bin2expstr(f'{i:05b}', 'p')))

    primes = expr2bdd(primesExpressions[0])
    for primeStart in primesExpressions:
        primes |= expr2bdd(primeStart)

    # get BDD variables from BDD's
    x0, x1, x2, x3, x4, y0, y1, y2, y3, y4 = G.inputs
    p0, p1, p2, p3, p4 = primes.inputs
    z0, z1, z2, z3, z4 = bddvars('z', 5)

    # primeStart is BDD for: starting from a prime
    primeStart = primes.compose({p0: x0, p1: x1, p2: x2, p3: x3, p4: x4})
    P = (primeStart & G)

    # init is BDD for: starting at a prime and reachable in two steps
    r1 = P.compose({y0: z0, y1: z1, y2: z2, y3: z3, y4: z4})
    r2 = G.compose({x0: z0, x1: z1, x2: z2, x3: z3, x4: z4})
    init = (r1 & r2).smoothing([z0, z1, z2, z3, z4])

    # twoSteps is BDD for: reachable in two steps
    g1 = G.compose({y0: z0, y1: z1, y2: z2, y3: z3, y4: z4})
    g2 = G.compose({x0: z0, x1: z1, x2: z2, x3: z3, x4: z4})
    twoSteps = (g1 & g2).smoothing([z0, z1, z2, z3, z4])

    # evenEnd is BDD for: ends on an even
    evenEnd = expr2bdd(~y4)

    # result is BDD for: starts on prime and reaches an even in even numbersteps 
    # it is initially the BDD for: starts on a prime, travels two steps, and
    # ends on an even
    result = init & evenEnd

    # generate 2 steps, 4 steps, etc... BDD's and OR them with result
    curEven = init
    # twosteps z -> y
    twoSteps = twoSteps.compose({x0: z0, x1: z1, x2: z2, x3: z3, x4: z4})
    for i in range(32):
        # temp x -> z
        curEven = curEven.compose({y0: z0, y1: z1, y2: z2, y3: z3, y4: z4})
        curEven = (curEven & twoSteps).smoothing([z0, z1, z2, z3, z4])
        temp = (curEven & evenEnd)
        result |= temp

    printBDD(result)

    requirement = primeStart & evenEnd

    print('result is requirement:', result is requirement)

# The resulting BDD is equal to the primes BDD with the extra restriction of ~y4
# So the property:
# """
# for each node u in [prime], there is a node v in [even] such that u can reach 
# v in even number of steps
# """
# is true for this graph
