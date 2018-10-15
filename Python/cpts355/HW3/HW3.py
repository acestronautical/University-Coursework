from functools import reduce
import unittest
import sys
            
# P1 A

# helper


def addDicts(d1, d2):
    _d = d1.copy()
    for key, value in d2.items():
        if key not in _d:
            _d.update({key: value})
        else:
            _d[key] += value
    return _d


def addDict(d):
    _d = dict()
    for _, week in d.items():
        _d = addDicts(_d, week)
    return _d


class TestAddDict(unittest.TestCase):
    def test(self):
        self.fun = addDict
        self.check = lambda case, result: self.assertDictEqual(
            addDict(case), result)
        self.cases = [
            {},
            {'355': {'Mon': 3, 'Wed': 2, 'Sat': 2},
             '360': {'Mon': 3, 'Tue': 2, 'Wed': 2, 'Fri': 10},
             '321': {'Tue': 2, 'Wed': 2, 'Thu': 3},
             '322': {'Tue': 1, 'Thu': 5, 'Sat': 2}}
        ]
        self.results = [
            {},
            {'Fri': 10, 'Mon': 6, 'Sat': 4,
             'Thu': 8, 'Tue': 5, 'Wed': 6}
        ]
        for case, result in zip(self.cases, self.results):
            self.check(case, result)


# P1 B


def addDictN(L):
    weeks = map(addDict, L)
    _L = reduce(addDicts, weeks)
    return _L

class TestAddDictN(unittest.TestCase):
    def test(self):
        self.fun = addDictN
        self.cases = [
            [
            {'355': {'Mon': 3, 'Wed': 2, 'Sat': 2},
            '360': {'Mon': 3, 'Tue': 2, 'Wed': 2, 'Fri': 10},
            '321': {'Tue': 2, 'Wed': 2, 'Thu': 3},
            '322': {'Tue': 1, 'Thu': 5, 'Sat': 2}},
            {'322': {'Mon': 2},
            '360': {'Thu': 2, 'Fri': 5},
            '321': {'Mon': 1, 'Sat': 3}},
            {'355': {'Sun': 8},
            '360': {'Fri': 5},
            '321': {'Mon': 4},
            '322': {'Sat': 3}}
            ]
        ]
        self.results = [
            {'Fri': 20,'Mon': 13,'Sat': 10,'Sun': 8, 'Thu': 10, 'Tue': 5, 'Wed': 6}
        ]
        self.check = lambda case, result: self.assertEqual(self.fun(case), result)
        for case, result in zip(self.cases, self.results):
            self.check(case, result)

# P2 A


def lookupVal(L, k):
    for d in reversed(L):
        if k in d:
            return d[k]
    return None


class TestLookupVal(unittest.TestCase):
    def test(self):
        self.fun = lookupVal
        self.L1 = [{"x": 1, "y": True, "z": "found"}, {"x": 2}, {"y": False}]
        self.cases = [
                (self.L1, "x"),
                (self.L1, "y"),
                (self.L1, "z"),
                (self.L1, "t")
        ]
        self.results = [
            2,
            False,
            "found",
            None
        ]
        self.check = lambda case, result: self.assertEqual(self.fun(*case), result)
        for case, result in zip(self.cases, self.results):
            self.check(case, result)


# P2 B


def lookupVal2(tL, k):
    t = tL[-1]
    while True:
        if k in t[1]:
            return t[1][k]
        if t == tL[0]:
            return None
        else:
            t = tL[t[0]]


class TestLookupVal2(unittest.TestCase):
    def test(self):
        self.fun = lookupVal2
        self.L1 = [(0, {"x": 0, "y": True, "z": "zero"}), (0, {"x": 1}),
         (1, {"y": False}), (1, {"x": 3, "z": "three"}), (2, {})]
        self.cases = [
                (self.L1, "x"),
                (self.L1, "y"),
                (self.L1, "z"),
                (self.L1, "t")
        ]
        self.results = [
            1,
            False,
            "zero",
            None
        ]
        self.check = lambda case, result: self.assertEqual(self.fun(*case), result)
        for case, result in zip(self.cases, self.results):
            self.check(case, result)

# P3


def numPaths(m, n, blocks):
    paths = 0
    def robot(x, y):
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


class TestNumPaths(unittest.TestCase):
    def test(self):
        self.fun = numPaths
        self.L1 = [(0, {"x": 0, "y": True, "z": "zero"}), (0, {"x": 1}),
         (1, {"y": False}), (1, {"x": 3, "z": "three"}), (2, {})]
        self.cases = [
                (2, 2, [(2,1)]),
                (3,3,[(2,3)]),
                (4,3,[(2,2)]),
                (10,3,[(2,2),(7,1)])
        ]
        self.results = [
            1,
            3,
            4,
            27
        ]
        self.check = lambda case, result: self.assertEqual(self.fun(*case), result)
        for case, result in zip(self.cases, self.results):
            self.check(case, result)

# P4


def palindromes(S):
    _pals = []

    def mirrors(i, j):
        nonlocal S
        nonlocal _pals
        if S[i] == S[j]:
            if j - i > 0:
                _pals.append(S[i:j+1])
            if i > 0 and j < len(S) - 1:
                mirrors(i-1, j+1)
    for i in range(1, len(S)):
        mirrors(i, i)
        mirrors(i-1, i)
    return sorted(list(set(_pals)))

class TestPalindromes(unittest.TestCase):
    def test(self):
        self.fun = palindromes
        self.cases = [
            'cabbbaccab',
            ' bacdcabdbacdc',
            ' myracecars'
        ]
        self.results = [
            ['abbba', 'acca', 'baccab', 'bb', 'bbb', 'cabbbac', 'cc'],
            ['abdba', 'acdca', 'bacdcab', 'bdb', 'cabdbac', 'cdc', 'cdcabdbacdc','dcabdbacd'],
            ['aceca', 'cec', 'racecar']
        ]
        self.check = lambda case, result: self.assertEqual(self.fun(case), result)
        for case, result in zip(self.cases, self.results):
            self.check(case, result)


# P5 A


class iterApply:
    def __init__(self, start, fun):
        self.cur = start
        self.fun = fun

    def __iter__(self):
        return self

    def __next__(self):
        x, self.cur = self.cur, self.cur + 1
        return self.fun(x)

    def __prev__(self):
        x, self.cur = self.cur - 2, self.cur - 1
        return self.fun(x)

class TestIterApply(unittest.TestCase):
    def test(self):
        self.squares = iterApply(1, lambda x: x**2)
        self.squaresResults = [
            1,
            4,
            9
        ]
        self.triples = iterApply(1, lambda x: x**3)
        self.triplesResults = [
            1, 
            8,
            27
        ]
        for triple in self.triplesResults:
            self.assertEqual(self.triples.__next__(), triple)



# P5 B


def iMerge(iNumbers1, iNumbers2, N):
    _L = []
    x = iNumbers1.__next__()
    y = iNumbers2.__next__()
    while len(_L) < N:
        if x < y:
            _L.append(x)
            x = iNumbers1.__next__()
        else:
            _L.append(y)
            y = iNumbers2.__next__()
    iNumbers1.__prev__()
    iNumbers2.__prev__()
    _L.sort()
    return _L

class TestIMerge(unittest.TestCase):
    def test(self):
        self.fun = iMerge
        self.squares = iterApply(1, lambda x: x**2)
        self.triples = iterApply(1, lambda x: x**3)
        self.cases = [
            (self.squares, self.triples, 8),
            (self.squares, self.triples, 10),
            (self.squares, self.triples, 6) 
        ]
        self.results = [
            [1, 1, 4, 8, 9, 16, 25, 27],
            [36, 49, 64, 64, 81, 100, 121, 125, 144, 169],
            [196, 216, 225, 256, 289, 324]
        ]
        self.check = lambda case, result: self.assertEqual(self.fun(*case), result)
        for case, result in zip(self.cases, self.results):
            self.check(case, result)

# P6 A


class Stream(object):
    def __init__(self, first, compute_rest, empty=False):
        self.first = first
        self._compute_rest = compute_rest
        self.empty = empty
        self._rest = None
        self._computed = False

    @property
    def rest(self):
        assert not self.empty, 'Empty streams have no rest.'
        if not self._computed:
            self._rest = self._compute_rest()
            self._computed = True
        return self._rest


def make_integer_stream(first=1):
    def compute_rest():
        return make_integer_stream(first+1)
    return Stream(first, compute_rest)


empty_stream = Stream(None, None, True)


def streamRandoms(k, min, max):
    return


if __name__ == '__main__':
  suite = unittest.TestLoader().loadTestsFromModule( sys.modules[__name__] )
  unittest.TextTestRunner(verbosity=3).run( suite )