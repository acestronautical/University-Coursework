from functools import reduce
    
#P1 A

#helper
def addDicts(d1, d2):
    _d = d1.copy()
    for key, value in d2.items():
            if key not in _d:
                _d.update({key:value})
            else:
                _d[key] += value
    return _d

def addDict(d):
    _d = dict()
    for _, week in d.items():
        _d = addDicts(_d, week)
    return _d

studyHours = {'355':{'Mon':3,'Wed':2,'Sat':2},'360':{'Mon':3,'Tue':2,'Wed':2,'Fri':10},'321':{'Tue':2,'Wed':2,'Thu':3},'322':{'Tue':1,'Thu':5,'Sat':2}}
print(addDict(studyHours))

#P1 B
def addDictN(L):
    weeks = map(addDict, L)
    _L = reduce(addDicts, weeks)
    return _L

logs = [{'355':{'Mon':3,'Wed':2,'Sat':2},'360':{'Mon':3,'Tue':2,'Wed':2,'Fri':10},'321':{'Tue':2,'Wed':2,'Thu':3},'322':{'Tue':1,'Thu':5,'Sat':2}},{'322':{'Mon':2},'360':{'Thu':2, 'Fri':5},'321':{'Mon':1, 'Sat':3}},{'355':{'Sun':8},'360':{'Fri':5},'321':{'Mon':4},'322':{'Sat':3}}]
print(addDictN(logs))

#P2 A
def lookupVal(L, k):
    for d in reversed(L):
        if k in d:
            return d[k]
    return None            
L1 = [{"x":1,"y":True,"z":"found"},{"x":2},{"y":False}]
print(lookupVal(L1,"x"))
print(lookupVal(L1,"y"))
print(lookupVal(L1,"z"))
print(lookupVal(L1,"t"))

#P2 B
def lookupVal2(tL, k):
    t = tL[-1]
    while True:
        if k in t[1]:
            return t[1][k]
        if t == tL[0]:
            return None
        else:
            t = tL[t[0]]

L2 = [(0,{"x":0,"y":True,"z":"zero"}),(0,{"x":1}),(1,{"y":False}),(1,{"x":3, "z":"three"}),(2,{})]
print(lookupVal2(L2,"x"))
print(lookupVal2(L2,"y"))
print(lookupVal2(L2,"z"))
print(lookupVal2(L2,"t"))

#P3
def numPaths(m, n, blocks):
    paths = 0
    def robot(x , y):
        nonlocal paths
        if x == m and y == n:
            paths = paths + 1
        elif x > m or y > n:
            return
        elif (x, y) in blocks:
            return
        else:
            robot(x + 1, y)
            robot(x, y + 1)
        return paths
    return robot(1, 1)
    
print(numPaths(2,2,[(2,1)]))
print(numPaths(3,3,[(2,3)])) 
print(numPaths(4,3,[(2,2)]) )
print(numPaths(10,3,[(2,2),(7,1)]))

#P4
