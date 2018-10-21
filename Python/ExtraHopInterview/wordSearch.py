import string

# global constants
TestWordGrid = [
    ['Q', 'W', 'E', 'R', 'T', 'N', 'U', 'I'],
    ['O', 'P', 'A', 'A', 'D', 'F', 'G', 'H'],
    ['T', 'K', 'L', 'Z', 'X', 'C', 'V', 'B'],
    ['N', 'M', 'R', 'W', 'F', 'R', 'T', 'Y'],
    ['U', 'I', 'O', 'P', 'A', 'S', 'D', 'F'],
    ['G', 'H', 'J', 'O', 'L', 'Z', 'X', 'C'],
    ['V', 'B', 'N', 'M', 'Q', 'W', 'E', 'R'],
    ['T', 'Y', 'U', 'I', 'O', 'P', 'A', 'S']
]

WordGrid = [
    ['E', 'X', 'T', 'R', 'A', 'H', 'O', 'P'],
    ['N', 'E', 'T', 'W', 'O', 'R', 'K', 'S'],
    ['Q', 'I', 'H', 'A', 'C', 'I', 'Q', 'T'],
    ['L', 'F', 'U', 'N', 'U', 'R', 'X', 'B'],
    ['B', 'W', 'D', 'I', 'L', 'A', 'T', 'V'],
    ['O', 'S', 'S', 'Y', 'N', 'A', 'C', 'K'],
    ['Q', 'W', 'O', 'P', 'M', 'T', 'C', 'P'],
    ['K', 'I', 'P', 'A', 'C', 'K', 'E', 'T']
]

puncRemover = str.maketrans('', '', string.punctuation)


# Trie


class TrieNode:
    """ TrieNode makes up the Trie data structure
    .keys contains dictionary of child nodes
    .word contains word hit or empty if not a hit
    """

    def __init__(self):
        self.keys = {}
        self.word = ""


class Trie:
    """ Trie is a tree of letters for word lookup
    """

    def __init__(self):
        self.root = TrieNode()

    def insert(self, word):
        """ insert is a case insensitive function
        which adds a word to the Trie
        """
        word = word.lower()

        def insertHelper(s, node):
            """ insertHelper is a recursive closure
            which drives insert
            """
            nonlocal word
            if not s:
                node.word = word
                return
            if s[0] not in node.keys:
                node.keys[s[0]] = TrieNode()
            insertHelper(s[1:], node.keys[s[0]])

        insertHelper(word, self.root)

    def prefix(self, word):
        """ prefix checks if word is
        a valid prefix to a word in the Trie
        note: a word is a valid prefix for itself
        """
        if self.containsFullCompare(word) > -1:
            return True
        return False

    def contains(self, word):
        """ contains checks if word is found in the Trie
        """
        if self.containsFullCompare(word) > 0:
            return True
        return False

    def containsFullCompare(self, word):
        """ containsFullCompare traverses the Trie
        returns 1 if word is found in Trie
        returns 0 if word is a prefix to a word in Trie
        returns -1 if word deadends i.e is not found or prefix
        """
        word = word.lower()

        def containsHelper(s, node):
            """ containsHelper is a recursive closure
            which drives containsFullCompare
            """
            nonlocal word
            if not s and node.word:
                return 1
            if not s:
                return 0
            if s[0] not in node.keys:
                return -1
            return containsHelper(s[1:], node.keys[s[0]])

        return containsHelper(word, self.root)


def NewTrieFromText(path):
    """ NewTrieFromText inserts all words from
    a given text file into the Trie
    removes punctuation (note: Trie is not case sensative)
    """
    trie = Trie()
    file = open(path)
    for line in file:
        for word in line.split():
            word = word.translate(puncRemover)
            trie.insert(word)
    return trie

# knightmove word search method


def KnightsMoveWordSearch(trie, grid):
    """KnightsMoveWordSearch recursively checks all knights moves
    from all starting positions recursively, and for all  
    words being constructed if the word is found in the Trie (add to return list),
    is a prefix in the Trie (continue constructing word), 
    or is a deadend in the Trie (short circuit return)
    """
    foundSet = set()

    def generateWords(i, j, word):
        """ generateWords is a recursive closure
        which drives KnightsMoveWordSearch
        """
        nonlocal grid
        nonlocal trie
        if i < 0 or i >= len(grid) or j < 0 or j >= len(grid[i]):
            return
        wordPlusChar = word + grid[i][j]
        if trie.contains(wordPlusChar):
            foundSet.add(wordPlusChar)
        if not trie.prefix(wordPlusChar):
            return
        generateWords(i - 1, j - 2, wordPlusChar)
        generateWords(i - 1, j + 2, wordPlusChar)
        generateWords(i + 1, j - 2, wordPlusChar)
        generateWords(i + 1, j + 2, wordPlusChar)
        generateWords(i - 2, j - 1, wordPlusChar)
        generateWords(i - 2, j + 1, wordPlusChar)
        generateWords(i + 2, j - 1, wordPlusChar)
        generateWords(i + 2, j + 1, wordPlusChar)

    for row, rowval in enumerate(grid):
        for col, _ in enumerate(rowval):
            generateWords(row, col, "")
    return list(foundSet)

# main


if __name__ == '__main__':

    # print test case
    print("\n\nTEST CASE")
    TestTrie = NewTrieFromText("testWords.txt")
    FoundList = KnightsMoveWordSearch(TestTrie, TestWordGrid)
    print("\nFound Words:")
    print(FoundList)
    print("\nLongest Word:")
    print(max(FoundList, key=len))  # FORTRAN

    # print solution
    print("\n\nSOLUTION")
    TrieLoveLost = NewTrieFromText("lovesLaboursLost.txt ")
    FoundList = KnightsMoveWordSearch(TrieLoveLost, WordGrid)
    print("\nFound Words:")
    print(FoundList)
    print("\nLongest Word:")
    print(max(FoundList, key=len))  # HONORIFICABILITUDINITATIBUS
