import re
# ------------------------- 10% ------------------------------------
# # The operand stack: define the operand stack and its operations

opstack = []
dictstack = [{}]


# now define functions to push and pop values to the top of to/from the top of
# the stack (end of the list). Recall that `pass` in Python is a space holder: replace it with your code.


def opPopN(N):
    if len(opstack) >= N:
        return tuple(opstack.pop() for _ in range(0, N))
    else:
        raise IndexError("attempt to pop opstack bottom")


def opPop():
    return opPopN(1)[0]


def opPushN(*items):
    for item in items:
        opstack.append(item)


def opPush(item):
    opPushN(item)

# Remember that there is a Postscript operator called "pop" so we choose
# different names for these functions.

 # --------------------------  ------------------------------------
 # # Type checking: check popped types are valid
 
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



 # -------------------------- 20% ------------------------------------
 # # The dictionary stack: define the dictionary stack and its operations


def dictPopN(N):
    if len(dictstack) >= N:
        return tuple(dictstack.pop() for _ in range(0, N))
    else:
        raise IndexError("attempt to pop dictstack bottom")


def dictPop():
    return dictPopN(1)[0]


def dictPushN(*items):
    for item in items:
        dictstack.append(item)


def dictPush(item):
    dictPushN(item)


# dictPush pushes a new dictionary to the dictstack. Note that, your interpreter
# will call dictPush only when Postscript “begin” operator is called. “begin”
# should pop the empty dictionary from the opstack and push it onto the dictstack
# by calling dictPush. You may either pass this dictionary (which you popped from
# opstack) to dictPush as a parameter or just simply push a new empty dictionary
# in dictPush.

def define(name, value):
    if isinstance(name, str) and name[0] == "/":
        dictstack[-1][name] = value
    else:
        raise TypeError("name is not a valid string")

# define adds name:value to the top dictionary in the dictionary stack. (Keep the ‘/’ in
# name when you add it to the top dictionary) Your psDef function should pop the
# name and value from operand stack and call the “define” function.


def lookup(name):
    for dic in dictstack:
        if "/" + name in dic:
            return dic["/" + name]
    raise ValueError("attempt to access undefined name")

 # lookup returns the value associated with name.
 # What is your design decision about what to do when there is no definition for
 # name? If “name” is not defined, your program should not break, but should
 # give an appropriate error message.


# --------------------------- 15% ------------------------------------
# # Arithmetic and comparison operators:
# define all the arithmetic and comparison operators here
#  --> add, sub, mul, div, eq, lt, gt
# Make sure to check the operand stack has the correct number of parameters
# and types of the parameters are correct.


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


# --------------------------- 15% ------------------------------------
# # Array operators: define the array operators length, get

def length():
    L = opPop()
    checkIsList(L)
    opPush(len(L))

def get():
    opand2, opand1 = opPopN(2)
    checkIsList(opand1)
    checkIsInteger(opand2)
    opPush(opand1[opand2])


# --------------------------- 15% ------------------------------------
# # Boolean operators: define the boolean operators psAnd, psOr, psNot
# Remember that these take boolean operands only. Anything else is an error



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


# --------------------------- 25% ------------------------------------
# # Define the stack manipulation and print operators:
# dup, exch, pop, copy, clear, stack

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

# --------------------------- 20% ------------------------------------
# # Define the dictionary manipulation operators: psDict, begin, end, psDef
# name the function for the def operator psDef because def is reserved in Python.
# Note: The psDef operator will pop the value and name from the opstack
# and call your own "define" operator (pass those values as parameters).
# Note that psDef()won't have any parameters.

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


# Important Note: For all operators you need to implement basic checks, i.e., check whether there are
# sufficient number of values in the operand stack and check whether those values have correct types.
# Examples:
# def operator: the operands stack should have 2 values where the second value from top of the stack is
# a string starting with '/'
# get operator : the operand stack should have 2 values; the top value on the stack should be an integer
# and the second value should be an array constant.

 # --------------------------- TEST FUNCTIONS ----------------------------------
 # # Include your test functions here

def testDefine():
    define("/n1", 4)
    if lookup("n1") != 4:
        return False
    return True

def testLookup():
    opPush("/n1")
    opPush(3)
    psDef()
    if lookup("n1") != 3:
        return False
    return True

#Arithmatic operator tests
def testAdd():
    opPush(1)
    opPush(2)
    add()
    if opPop() != 3:
        return False
    return True

def testSub():
    opPush(10)
    opPush(4.5)
    sub()
    if opPop() != 5.5:
        return False
    return True

def testMul():
    opPush(2)
    opPush(4.5)
    mul()
    if opPop() != 9:
        return False
    return True

def testDiv():
    opPush(10)
    opPush(4)
    div()
    if opPop() != 2.5:
        return False
    return True
    
#Comparison operators tests
def testEq():
    opPush(6)
    opPush(6)
    eq()
    if opPop() != True:
        return False
    return True

def testLt():
    opPush(3)
    opPush(6)
    lt()
    if opPop() != True:
        return False
    return True

def testGt():
    opPush(3)
    opPush(6)
    gt()
    if opPop() != False:
        return False
    return True

#boolean operator tests
def testPsAnd():
    opPush(True)
    opPush(False)
    psAnd()
    if opPop() != False:
        return False
    return True

def testPsOr():
    opPush(True)
    opPush(False)
    psOr()
    if opPop() != True:
        return False
    return True

def testPsNot():
    opPush(True)
    psNot()
    if opPop() != False:
        return False
    return True

#Array operator tests
def testLength():
    opPush([1,2,3,4,5])
    length()
    if opPop() != 5:
        return False
    return True

def testGet():
    opPush([1,2,3,4,5])
    opPush(4)
    get()
    if opPop() != 5:
        return False
    return True

#stack manipulation functions
def testDup():
    opPush(10)
    dup()
    if opPop()!=opPop():
        return False
    return True

def testExch():
    opPush(10)
    opPush("/x")
    exch()
    if opPop()!=10 and opPop()!="/x":
        return False
    return True

def testPop():
    l1 = len(opstack)
    opPush(10)
    pop()
    l2= len(opstack)
    if l1!=l2:
        return False
    return True

def testCopy():
    opPush(1)
    opPush(2)
    opPush(3)
    opPush(4)
    opPush(5)
    opPush(2)
    copy()
    if opPop()!=5 and opPop()!=4 and opPop()!=5 and opPop()!=4 and opPop()!=3 and opPop()!=2:
        return False
    return True

def testClear():
    opPush(10)
    opPush("/x")
    clear()
    if len(opstack)!=0:
        return False
    return True

#dictionary stack operators
def testDict():
    opPush(1)
    psDict()
    if opPop()!={}:
        return False
    return True

def testBeginEnd():
    opPush("/x")
    opPush(3)
    psDef()
    opPush({})
    begin()
    opPush("/x")
    opPush(4)
    psDef()
    end()
    if lookup("x")!=3:
        return False
    return True

def testpsDef():
    opPush("/x")
    opPush(10)
    psDef()
    if lookup("x")!=10:
        return False
    return True

def testpsDef2():
    opPush("/x")
    opPush(10)
    psDef()
    opPush(1)
    psDict()
    begin()
    if lookup("x")!=10:
        end()
        return False
    end()
    return True


def main_part1():
    testCases = [('define',testDefine),('lookup',testLookup),('add', testAdd), ('sub', testSub),('mul', testMul),('div', testDiv), \
                 ('eq',testEq),('lt',testLt),('gt', testGt), ('psAnd', testPsAnd),('psOr', testPsOr),('psNot', testPsNot), \
                 ('length', testLength),('get', testGet), ('dup', testDup), ('exch', testExch), ('pop', testPop), ('copy', testCopy), \
                 ('clear', testClear), ('dict', testDict), ('begin', testBeginEnd), ('psDef', testpsDef), ('psDef2', testpsDef2)]
    # add you test functions to this list along with suitable names
    failedTests = [testName for (testName, testProc) in testCases if not testProc()]
    if failedTests:
        return ('Some tests failed', failedTests)
    else:
        return ('All part-1 tests OK')


if __name__ == '__main__':
    print(main_part1())
