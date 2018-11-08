import re
from enum import Enum

# ------------------------- Globals ------------------------------------

opstack = []

dictstack = [{}]


# ------------------------- Utility ------------------------------------
# # Utility Functions: pop, push


def popN(D, N):
    if len(D) >= N:
        if N == 1:
            return D.pop()
        else:
            return tuple(D.pop() for _ in range(0, N))
    else:
        raise IndexError("attempt to pop stack bottom")


def pushN(D, *items):
    for item in items:
        D.append(item)

# ------------------------- Type Checking ------------------------------------
# # Type Check Functions: checkIs- Bool, Integer, Number, List, Dict


def checkIsBool(*items):
    for item in items:
        if not isinstance(item, bool):
            raise TypeError("cannot perform operation on non boolean type")


def checkIsInteger(*items):
    for item in items:
        if not isinstance(item, int):
            raise TypeError("cannot perform operation on non integer type")


def checkIsNumber(*items):
    for item in items:
        if not isinstance(item, (int, float)):
            raise TypeError("cannot perform operation on non number type")


def checkIsList(*items):
    for item in items:
        if not isinstance(item, list):
            raise TypeError("cannot perform operation on non list type")


def checkIsDict(*items):
    for item in items:
        if not isinstance(item, dict):
            raise TypeError("cannot perform operation on non dict type")

# ------------------------- Operand Stack ------------------------------------
# # Operand Stack Functions: opPop, opPopN, opPush, opPushN


def opPopN(N):
    return popN(opstack, N)


def opPop():
    return opPopN(1)


def opPushN(*items):
    pushN(opstack, *items)


def opPush(item):
    opPushN(item)

 # -------------------------- Dictionary Stack ------------------------------------
 # # Dictionary Stack Functions: dictPop, dictPopN, dictPush, dictPushN , define, lookup


def dictPopN(N):
    return popN(dictstack, N)


def dictPop():
    return dictPopN(1)


def dictPushN(*items):
    pushN(dictstack, *items)


def dictPush(item):
    dictPushN(item)


def define(name, value):
    if isinstance(name, str) and name[0] == "/":
        dictstack[-1][name] = value
    else:
        raise TypeError("name is not a valid string")


def lookup(name):
    for dic in dictstack:
        if "/" + name in dic:
            return dic["/" + name]
    raise ValueError("attempt to access undefined name")


# --------------------------- Arithmetic Operators ------------------------------------
# # Arithmetic Operator Functions: sub, add, div, mul, mod, neg, gt, lt, eq


def sub():
    opand2, opand1 = opPopN(2)
    checkIsNumber(opand1, opand2)
    opPush(opand1 - opand2)


def add():
    opand2, opand1 = opPopN(2)
    checkIsNumber(opand1, opand2)
    opPush(opand1 + opand2)


def div():
    opand2, opand1 = opPopN(2)
    checkIsNumber(opand1, opand2)
    opPush(opand1 / opand2)


def mul():
    opand2, opand1 = opPopN(2)
    checkIsNumber(opand1, opand2)
    opPush(opand1 * opand2)


def mod():
    opand2, opand1 = opPopN(2)
    checkIsNumber(opand1, opand2)
    opPush(opand1 % opand2)


def neg():
    opand1 = opPop()
    checkIsNumber(opand1)
    opPush(opand1 * -1)


def gt():
    opand2, opand1 = opPopN(2)
    checkIsNumber(opand1, opand2)
    opPush(opand1 > opand2)


def lt():
    opand2, opand1 = opPopN(2)
    checkIsNumber(opand1, opand2)
    opPush(opand1 < opand2)


def eq():
    opand2, opand1 = opPopN(2)
    checkIsNumber(opand1, opand2)
    opPush(opand1 == opand2)


# --------------------------- Array Operators ------------------------------------
# # Array Operators Functions: length, get

def length():
    L = opPop()
    checkIsList(L)
    opPush(len(L))


def get():
    opand2, opand1 = opPopN(2)
    checkIsList(opand1)
    checkIsInteger(opand2)
    opPush(opand1[opand2])


# --------------------------- Boolean Operators ------------------------------------
# # Boolean Operator Functions: psAnd, psOr, psNot


def psAnd():
    opand2, opand1 = opPopN(2)
    checkIsBool(opand1, opand2)
    opPush(opand1 and opand2)


def psOr():
    opand2, opand1 = opPopN(2)
    checkIsBool(opand1, opand2)
    opPush(opand1 or opand2)


def psNot():
    opand1 = opPop()
    checkIsBool(opand1)
    opPush(not opand1)


# --------------------------- Operand Stack Manipulation ------------------------------------
# # Stack Manipulation and Print Functions: dup, exch, pop, copy, clear, stack

def dup():
    opand1 = opPop()
    opPushN(opand1, opand1)


def exch():
    opand2, opand1 = opPopN(2)
    opPushN(opand2, opand1)


def pop():
    opPop()


def copy():
    N = opPop()
    checkIsInteger(N)
    opTuple = opPopN(N)
    opPushN(*(opTuple[::-1]))
    opPushN(*(opTuple[::-1]))


def clear():
    global opstack
    opstack = []


def stack():
    for item in opstack:
        print(item)

# --------------------------- Dictionary Stack Manipulation ------------------------------------
# # Dictionary Manipulation Functions: psDict, begin, end, psDef


def psDict():
    opand1 = opPop()
    checkIsInteger(opand1)
    opPush(dict())


def begin():
    opand1 = opPop()
    checkIsDict(opand1)
    dictPush(opand1)


def end():
    dictPop()


def psDef():
    value, name = opPopN(2)
    define(name, value)


 # --------------------------- Lexing and Parsing ----------------------------------
 # # Tokenizing, Group Matching, Classification

tokenRx = re.compile(r'''
    (\s+) |                       # whitespace
    (\d+\.\d+) |                  # float
    (\d+) |                       # integer
    (true|false) |                # boolean
    (\[[0-9\s\.]*\]) |         # array
    (add|sub|mul|div|neg|eq|lt|gt|and|or|not|length|get|dup|exch|pop|copy|clear|dict|begin|end|def|stack) |# operator
    (/[A-Za-z_][A-Za-z0-9_]*) |   # name
    ([A-Za-z_][A-Za-z0-9_]*) |    # variable
    ({) |                         # left brace
    (}) |                         # right brace
    (.)                           # an error!
    ''', re.DOTALL | re.VERBOSE)

    
s_to_op = {
    'add': add, 
    'sub': sub, 
    'mul': mul, 
    'div': div,
    'neg': neg,
    'eq': eq, 
    'lt': lt, 
    'gt': gt, 
    'and': psAnd,
    'or': psOr,
    'not': psNot,
    'length': length,
    'get': get, 
    'dup': dup, 
    'exch': exch, 
    'pop': pop, 
    'copy': copy,
    'clear': clear, 
    'dict': psDict, 
    'begin': begin, 
    'end': end, 
    'def': psDef, 
    'stack': stack,
    }

class token_type(Enum):
        floating = 1
        integer = 2 
        boolean = 3
        array = 9
        operator = 4
        name = 5
        variable =6
        left_brace = 7
        right_brace = 8
        code_block = 9
        

class Token:
    def __init__(self, token_type, token_data):
        self.token_type = token_type
        self.token_data = token_data

class Tokenizer:
    def __init__(self, s):
         self.matches = re.finditer(tokenRx, s)

    def __iter__(self):
        for match in self.matches:
            space, floatingS, integerS, booleanS, arrayS, operatorS, \
            nameS, variableS, left_braceS, right_braceS, unknownS = match.groups()
            if space:
                pass
            elif floatingS:
                self.current = Token(token_type.floating, float(floatingS))
            elif integerS:
                self.current = Token(token_type.integer, int(integerS))
            elif booleanS:
                self.current = Token(token_type.boolean, bool(booleanS))
            elif arrayS:
                self.current = Token(token_type.array, list(arrayS))
            elif operatorS:
                self.current = Token(token_type.operator, s_to_op[operatorS])
            elif nameS:
                self.current = Token(token_type.name, nameS)            
            elif variableS:
                self.current = Token(token_type.variable, variableS)                        
            elif left_braceS:
                self.current = Token(token_type.left_brace, left_braceS)
            elif right_braceS:
                self.current = Token( token_type.right_brace, right_braceS)
            elif unknownS: 
                raise NameError
            yield self.current


def groupMatching(it):
    token_sublist = []
    for t in it:
        if t.token_type == token_type.right_brace:
            return Token(token_type.code_block, token_sublist)
        elif t.token_type == token_type.left_brace:
            token_sublist.append(groupMatching(it))
        else:
            token_sublist.append(t)
    return False

def parse(s):
    token_list = []
    tIter = Tokenizer(s)
    for t in tIter:
        if t.token_type == token_type.right_brace:
            return False
        elif t.token_type == token_type.left_brace:
            token_list.append(groupMatching(tIter))
        else:
            token_list.append(t)
    return token_list


 # --------------------------- Interpreter ----------------------------------
 # # Run output of parsing

def interpreter(s):
    token_list = parse(s)
    for t in token_list:
        if t.token_type == token_type.variable:
            opPush(lookup(t.token_data))
        elif t.token_type == token_type.operator:
            t.token_data()
        else:
            opPush(t.token_data)

 # --------------------------- Test Functions ----------------------------------
 # # Include your test functions here

def testDefine():
    define("/n1", 4)
    return lookup("n1") == 4


def testLookup():
    opPushN("/n1", 3)
    psDef()
    return lookup("n1") == 3

# Arithmatic operator tests


def testAdd():
    opPushN(1, 2)
    add()
    return opPop() == 3


def testSub():
    opPushN(10, 4.5)
    sub()
    return opPop() == 5.5


def testMul():
    opPushN(2, 4.5)
    mul()
    return opPop() == 9


def testDiv():
    opPushN(10, 4)
    div()
    return opPop() == 2.5

# Comparison operators tests


def testEq():
    opPushN(6, 6)
    eq()
    return opPop() == True


def testLt():
    opPushN(3, 6)
    lt()
    return opPop() == True


def testGt():
    opPushN(3, 6)
    gt()
    return opPop() == False

# boolean operator tests


def testPsAnd():
    opPushN(True, False)
    psAnd()
    return opPop() == False


def testPsOr():
    opPushN(True, False)
    psOr()
    return opPop() == True


def testPsNot():
    opPush(True)
    psNot()
    return opPop() == False

# Array operator tests


def testLength():
    opPush([1, 2, 3, 4, 5])
    length()
    return opPop() == 5


def testGet():
    opPush([1, 2, 3, 4, 5])
    opPush(4)
    get()
    return opPop() == 5

# stack manipulation functions


def testDup():
    opPush(10)
    dup()
    return opPop() == opPop()


def testExch():
    opPush(10)
    opPush("/x")
    exch()
    return opPop() == 10 and opPop() == "/x"


def testPop():
    l1 = len(opstack)
    opPush(10)
    pop()
    l2 = len(opstack)
    return l1 == l2


def testCopy():
    opPushN(1, 2, 3, 4, 5, 2)
    copy()
    return opPop() == 5 and opPop() == 4 and opPop() == 5 and opPop() == 4 and opPop() == 3 and opPop() == 2


def testClear():
    opPushN(10, "/x")
    clear()
    return len(opstack) == 0

# dictionary stack operators


def testDict():
    opPush(1)
    psDict()
    return opPop() == {}


def testBeginEnd():
    opPushN("/x", 3)
    psDef()
    opPush({})
    begin()
    opPush("/x")
    opPush(4)
    psDef()
    end()
    return lookup("x") == 3


def testpsDef():
    opPushN("/x", 10)
    psDef()
    return lookup("x") == 10


def testpsDef2():
    opPush("/x")
    opPush(10)
    psDef()
    opPush(1)
    psDict()
    begin()
    if lookup("x") != 10:
        end()
        return False
    end()
    return True

# Lexing tests

def testGroup():
    return parse("{{}{{}}}") == [[[], [[]]]]


 # --------------------------- Main Function ----------------------------------

def test_results():
    testCases = [
    ('define', testDefine), 
    ('lookup', testLookup), 
    ('add', testAdd), 
    ('sub', testSub), 
    ('mul', testMul), 
    ('div', testDiv),
    ('eq', testEq), 
    ('lt', testLt), 
    ('gt', testGt), 
    ('psAnd', testPsAnd),
    ('psOr', testPsOr),
    ('psNot', testPsNot),
    ('length', testLength),
    ('get', testGet), 
    ('dup', testDup), 
    ('exch', testExch), 
    ('pop', testPop), 
    ('copy', testCopy),
    ('clear', testClear), 
    ('dict', testDict), 
    ('begin', testBeginEnd), 
    ('psDef', testpsDef), 
    ('psDef2', testpsDef2),
    ('group', testGroup),
    ]
    # add you test functions to this list along with suitable names
    failedTests = [testName for (testName, testProc) in testCases if not testProc()]
    if failedTests:
        return ('Some tests failed', failedTests)
    else:
        return ('All tests OK')
        
if __name__ == '__main__':
    print(test_results())
