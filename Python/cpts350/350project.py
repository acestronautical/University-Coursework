#!/usr/bin/env python3
from pyeda.inter import *
from graphviz import Source

def printBDD(bdd):
    Source(bdd.to_dot(), filename="test.gv", format="png").view()

evens = []
for i in range(0, 32):
    if i % 2 == 0:
        evens.append(f'{i:05b}')
print('evens', evens)

primes = []
primesList = [3, 5, 7, 11, 13, 17, 19, 23, 29, 31]
for i in range(0, 32):
    if i in primesList:
        primes.append(f'{i:05b}')
print('primes', primes)

edgePairs = []
for i in range(0, 32):
    for j in range(0, 32):
        if ((i + 3) % 32 == j % 32) or ((i + 8) % 32 == j % 32):
            edgePairs.append((f'{i:05b}', f'{j:05b}'))


edgeExpressions = []
for p1, p2 in edgePairs:
    exp = ''
    for idx in range( len(p1)):
        if p1[idx] == '1':
            exp += 'x'
        elif p1[idx] == '0':
            exp += '~x'
        exp += str(idx) + ' & '
    for idy in range ( len(p2)):
        if p2[idy] == '1':
            exp += 'y'
        elif p2[idy] == '0':
            exp += '~y'
        exp += str(idy) + ' & '
    edgeExpressions.append(expr(exp[:-3]))

edgeBDDs = [expr2bdd(x) for x in edgeExpressions]

R = edgeBDDs[0]
for b in edgeBDDs:
    R |= b