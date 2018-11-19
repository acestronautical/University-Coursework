# Author: Ace Cassidy
import re
from enum import Enum
# ------------------------- Globals ------------------------------------

class mode(Enum):
    Dynamic = 1
    Static = 2

interpretMode = mode.Dynamic

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
    for dic in dictstack[::-1]:
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

# --------------------------- Data Flow Operators ------------------------------------
# # Looping and conditionals: if, elseif, for, forall
def psIf():
    # <bool> <code-array> if
    opand2, opand1 = opPopN(2)
    checkIsBool(opand1)
    if opand1:
        interpret(opand2.data)

def psIfElse():
    # <bool> <code-array1> <code-array2> ifelse
    opand3, opand2, opand1 = opPopN(3)
    checkIsBool(opand1)
    if opand1:
        interpret(opand2.data)
    else:
        interpret(opand3.data)

def psFor():
    # <init> <incr> <final> <code array> for 
    opand4, opand3, opand2, opand1 = opPopN(4)
    checkIsInteger(opand1, opand2, opand3)
    while opand1 != opand3:
        opPush(opand1)
        interpret(opand4.data)
        opand1 += opand2
    opPush(opand1)
    interpret(opand4.data)
    

def psForall():
    opand2, opand1 = opPopN(2)
    for item in opand1:
        opPush(item)
        interpret(opand2.data)

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
    for item in opstack[::-1]:
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


token_pattern = re.compile(r'''
    (?P<space>\s+) |                       # whitespace
    (?P<floating>-?\d+\.\d+) |             # float
    (?P<integer>-?\d+) |                   # integer
    (?P<boolean>true|false) |              # boolean
    (?P<array>\[[0-9\s\.]*\]) |            # array
    (?P<name>/[A-Za-z_][A-Za-z0-9_]*) |    # name
    (?P<operator>add|sub|mul|div|neg|eq|lt|gt|and|or|not|length|get|dup|exch|pop|copy|clear|dict|begin|end|def|stack|ifelse|if|forall|for) |# operator
    (?P<variable>[A-Za-z_][A-Za-z0-9_]*) | # variable
    (?P<left_brace>{) |                    # left brace
    (?P<right_brace>}) |                   # right brace
    (?P<unknown>.)                         # an error!
    ''', re.DOTALL | re.VERBOSE)


functionof = {
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
    'if': psIf,
    'ifelse': psIfElse,
    'for': psFor,
    'forall': psForall,
}

class operator: 
    def __init__(self, operator):
        self.data = operator

class variable: 
    def __init__(self, variable):
        self.data = variable

class left_brace:
    def __init__(self, left_brace):
        self.data = left_brace

class right_brace:
    def __init__(self, right_brace):
        self.data = right_brace

class code_block:
    def __init__(self, code_block):
        self.data = code_block

class Tokenizer:
    def __init__(self, s):
        self.matches = re.finditer(token_pattern, s)

    def __iter__(self):
        for match in self.matches:
            if match.group("space"):
                continue
            elif match.group("floating"):
                self.current = float(match.group("floating"))
            elif match.group("integer"):
                self.current = int(match.group("integer"))
            elif match.group("boolean"):
                self.current = bool(match.group("boolean"))
            elif match.group("array"):
                self.current = [eval(item) for item in match.group("array")[1:-1].split()]
            elif match.group("name"):
                self.current = match.group("name")
            elif match.group("operator"):
                self.current = operator(functionof[match.group("operator")])
            elif match.group("variable"):
                self.current = variable(match.group("variable"))
            elif match.group("left_brace"):
                self.current = left_brace(match.group("left_brace"))
            elif match.group("right_brace"):
                self.current = right_brace(match.group("right_brace"))
            elif match.group("unknown"):
                raise NameError
            else:
                continue
            yield self.current

def group(it):
    token_list = []
    for t in it:
        if type(t) is right_brace:
            return False
        elif type(t) is left_brace:
            token_list.append(group_helper(it))
        else:
            token_list.append(t)
    return token_list

def group_helper(it):
    token_sublist = []
    for t in it:
        if type(t) is right_brace:
            return code_block(token_sublist)
        elif type(t) is left_brace:
            token_sublist.append(group_helper(it))
        else:
            token_sublist.append(t)
    return False

def parse(s):
    it = Tokenizer(s)
    return group(it)

 # --------------------------- Interpreter ----------------------------------
 # # Run output of parsing

def setMode(s):
    global interpretMode
    if s == "dynamic" or s == mode.Dynamic:
        interpretMode = mode.Dynamic
    elif s == "static" or s == mode.Static:
        interpretMode = mode.Static
    else:
        raise ValueError("valid modes are 'static' or 'dynamic'")

def interpreter(s, mode = "dynamic"):
    setMode(mode) 
    tokens = parse(s)
    interpret(tokens)

def interpret(tokens):
    for t in tokens:
        if type(t) is variable:
            val = lookup(t.data)
            if type(val) is code_block:
                interpret(val.data)
            else:
                opPush(val)
        elif type(t) is operator:
            t.data()
        else:
            opPush(t)


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
def testInterpreter():
    interpreter("5 4 add")
    if opPop() != 9:
        return False
    interpreter("[9 9 8 4 10] { } forall")
    if opPopN(5) != (10, 4, 8, 9, 9):
        return False
    interpreter("[1 2 3 4 5] dup length exch {dup mul}  forall add add add add exch 0 exch -1 1 {dup mul add} for eq") 
    if opPop() != True:
        return False
    interpreter("/x 3 def x 3 eq {x   1    add} {x   1    sub} ifelse")
    if opPop() != 4:
        return False
    interpreter("/square {dup mul} def  [1 2 3 4] {square} forall add add add 30 eq true")
    if opPopN(2) != (True, True):
        return False
    interpreter("[1 2 3 4 5] dup length /n exch def /fact { 0 dict begin /n exch def n 2 lt { 1} {n 1 sub fact n mul } ifelse end } def n fact")    
    if opPopN(2) != (120, [1, 2, 3, 4, 5]):
        return False
    return True

def testInterpreterStatic():
    case1 = "/x 4 def /u { x stack } def /f { /x 7 def g } def f"
    interpreter(case1, "dynamic")
    if opPop() != 7: 
        return False
    interpreter(case1, "static")
    if opPop() != 4:
        return False
    return True

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
        ('interpreter', testInterpreter),
    ]
    # add you test functions to this list along with suitable names
    failedTests = [testName for (testName, testProc)
                   in testCases if not testProc()]
    if failedTests:
        return ('Some tests failed', failedTests)
    else:
        return ('All tests OK')


if __name__ == '__main__':
    print(test_results())
