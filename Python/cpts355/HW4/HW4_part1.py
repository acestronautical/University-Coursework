
# ------------------------- 10% ------------------------------------
# # The operand stack: define the operand stack and its operations

OperandStack = []

# now define functions to push and pop values to the top of to/from the top of
# the stack (end of the list). Recall that `pass` in Python is a space holder: replace it with your code.


def opPopN(N):
    if len(OperandStack) >= N:
        return tuple(OperandStack.pop() for _ in range(0, N))
    else:
        raise IndexError("attempted to pop more than operand stack depth")


def opPop():
    return opPopN(1)[0]


def opPushN(*items):
    for item in items:
        OperandStack.append(item)


def opPush(item):
    opPushN(item)

# Remember that there is a Postscript operator called "pop" so we choose
# different names for these functions.

 # -------------------------- 20% ------------------------------------
 # # The dictionary stack: define the dictionary stack and its operations


DictionaryStack = [{}]


def dictPopN(N):
    if len(DictionaryStack) >= N:
        return tuple(DictionaryStack.pop() for _ in range(0, N))
    else:
        raise IndexError("attempted to pop more than dictionary stack depth")


def dictPop():
    return dictPopN(1)[0]


def dictPushN(*items):
    for item in items:
        DictionaryStack.append(item)


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
        DictionaryStack[-1][name] = value
    else:
        raise TypeError("name is not a valid string")

# define adds name:value to the top dictionary in the dictionary stack. (Keep the ‘/’ in
# name when you add it to the top dictionary) Your psDef function should pop the
# name and value from operand stack and call the “define” function.


def lookup(name):
    for dic in DictionaryStack:
        if "/" + name in dic:
            return dic["/" + name]
    raise ValueError("attempted to access an undefined name")

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

def checkIsNumber(*items):
    for item in items:
        if not isinstance(item, (int, float)):
            raise TypeError("cannot perform operation on non number type")


def sub():
    opand1, opand2 = opPopN(2)
    checkIsNumber(opand1, opand2)
    opPush(opand1 - opand2)


def add():
    opand1, opand2 = opPopN(2)
    checkIsNumber(opand1, opand2)
    opPush(opand1 + opand2)


def div():
    opand1, opand2 = opPopN(2)
    checkIsNumber(opand1, opand2)
    opPush(opand1 / opand2)


def mul():
    opand1, opand2 = opPopN(2)
    checkIsNumber(opand1, opand2)
    opPush(opand1 * opand2)


def mod():
    opand1, opand2 = opPopN(2)
    checkIsNumber(opand1, opand2)
    opPush(opand1 % opand2)


def neg():
    opand1 = opPop()
    checkIsNumber(opand1)
    opPush(opand1 * -1)


def gt():
    opand1, opand2 = opPopN(2)
    checkIsNumber(opand1, opand2)
    opPush(opand1 > opand2)


def lt():
    opand1, opand2 = opPopN(2)
    checkIsNumber(opand1, opand2)
    opPush(opand1 < opand2)


def eq():
    opand1, opand2 = opPopN(2)
    checkIsNumber(opand1, opand2)
    opPush(opand1 == opand2)


# --------------------------- 15% ------------------------------------
# # Array operators: define the array operators length, get


# --------------------------- 15% ------------------------------------
# # Boolean operators: define the boolean operators psAnd, psOr, psNot
# Remember that these take boolean operands only. Anything else is an error

def checkIsBool(*items):
    for item in items:
        if not isinstance(item, bool):
            raise TypeError("cannot perform operation on non boolean type")


def psAnd():
    opand1, opand2 = opPopN(2)
    checkIsBool(opand1, opand2)
    opPush(opand1 and opand2)


def psOr():
    opand1, opand2 = opPopN(2)
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
    opand1, opand2 = opPopN(2)
    opPushN(opand1, opand2)


def pop():
    opPop()


def copy(N):
    opTuple = opPopN(N)
    opPushN(*(opTuple[::-1]), *(opTuple[::-1]))


def clear():
    global OperandStack
    OperandStack = []


def stack():
    for item in OperandStack:
        print(item)

# --------------------------- 20% ------------------------------------
# # Define the dictionary manipulation operators: psDict, begin, end, psDef
# name the function for the def operator psDef because def is reserved in Python.
# Note: The psDef operator will pop the value and name from the opstack
# and call your own "define" operator (pass those values as parameters).
# Note that psDef()won't have any parameters.


def psDict():
    opand1 = opPop()
    if isinstance(opand1, int):
        opPush(dict())
    else:
        raise TypeError("expected integer argument for dict")


def begin():
    opand1 = opPop()
    if isinstance(opand1, dict):
        dictPush(opand1)
    else:
        raise TypeError("top of stack was not type dict for begin")


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


def testpsDef():
    opPush("/n1")
    opPush(3)
    psDef()
    return (lookup("n1") == 3)

 # now an easy way to run all the test cases and make sure that they all return true is
if __name__ == '__main__':
    print(testpsDef())
    # add you test functions to this list along with suitable names
