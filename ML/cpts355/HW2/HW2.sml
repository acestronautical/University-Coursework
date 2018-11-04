(*
CptS355 - Assignment 2 (Standard ML)
Fall 2018
Assigned: Wednesday, September 19, 2018
Due: Monday, October 1, 2018

Author: Ace Cassidy
SID: 011418306
*)


(*From lecture slides*)
fun map f [] = [] 
| map f (x::rest) = (f x)::(map f rest);

fun fold f base [] = base  
| fold f base (x::rest) = f x (fold f base rest);

fun filter pred [] = [] 
| filter pred (x::rest) =  if pred x then x::(filter  pred rest) 
    else (filter pred rest);

fun revAppend [] L =L
| revAppend (x::rest) L = revAppend rest (x::L);

fun reverse L = revAppend L [];

(*1). numbersToSum and numbersToSumTail - 15%*)
(*a) (7%) The returned list should include the first n elements from the input list L such that 
the first n elements of the list add to less than sum, but the first (n + 1) elements of the list add to sum or more.
The type of numbersToSum should be int -> int list -> int list.*)

fun numbersToSum sum [] = []
| numbersToSum sum (x::rest) = 
  if (sum - x) <= 0 then [] else (x::(numbersToSum (sum - x) rest))

(*
Examples:
> numbersToSum 100 [10, 20, 30, 40]
[10, 20, 30]
> numbersToSum 30 [5, 4, 6, 10, 4, 2, 1, 5]
[5, 4, 6, 10, 4]
> numbersToSum 1 [2]
[]
> numbersToSum 1 []
[]
*)

(*b) (8%) Re-write the numbersToSum function from part (a) as a tail-recursive function.
The type of numbersToSumTail should be int -> int list -> int list.*)

fun numbersToSumTail sum L = 
let 
  fun numbersToSumSub sum [] L =  L
  | numbersToSumSub sum (x::rest) L = if (sum - x) <= 0 then (reverse L) else (numbersToSumSub (sum - x) rest (x::L))
in
  numbersToSumSub sum L []
end;

(*2). partition - 10%
returns a 2-tuple (pos,neg) as output where pos is the list of the elements in L for which F e i evaluated
true, and neg is the list of those elements in L for which F e i evaluated to false. The elements of
pos and neg retain the same relative order they possessed in L.
The type of the partition function should be ('a -> bool) -> 'a list -> 'a list * 'a list*)

(*helper function*)
fun negate F X = not (F X)

fun partition F L = ((filter F L),(filter (negate F) L))

(*Examples:
> partition (fn x => (x<=4)) [1,7,4,5,3,8,2,3]
([1,4,3,2,3],[7,5,8])
> partition null [[1,2],[1],[],[5],[],[6,7,8]]
([[],[]],[[1,2],[1],[5],[6,7,8]])
fun exists n [] = false
| exists n (x::rest) = if n=x then true else (exists n rest)
> partition (exists 1) [[1,2],[1],[],[5],[],[6,7,8]]
([[1,2],[1]],[[],[5],[],[6,7,8]])
> partition (fn x=> (x<=4)) []
([],[])
*)

(*3). areAllUnique - 10%
returns true if every element in the list appears only once, false otherwise.
The type of the areAllUnique function should be ''a list ->bool.*)

fun different x y = not (x = y)

fun areAllUnique [] = true
| areAllUnique (x::rest) = if length( x::(filter (different x) rest) ) <> length(x::rest) then false else (areAllUnique rest)

(*
Examples:
> areAllUnique [1,3,4,2,5,0,10]
true
> areAllUnique [[1,2],[3],[4,5],[]]
true
> areAllUnique [(1,"one"),(2,"two"),(1,"one")]
false
> areAllUnique []
true
> areAllUnique [1,2,3,4,1,7]
false
*)

(*4). sum, sumOption, and sumEither
(a) sum - 5%
returns the sum of all numbers in all sublists of the input list.
The type of the sum function should be int list list -> int.*)

fun f1 x y = x+y;

fun sum [] = 0
| sum (L: int list list) = fold f1 0 (map (fold f1 0) L)

(*
Examples:
> sum [[1,2,3],[4,5],[6,7,8,9],[]]
45
> sum [[10,10],[10,10,10],[10]]
60
> sum [[]]
0
> sum []
0
*)

(*b) sumOption - 10%
returns the sum of all int option values in all sublists of the input list.
The type of the sumOption function should be int option list list -> int option.*)

fun f2 NONE NONE = NONE
| f2 (SOME(x)) NONE = (SOME(x))
| f2 NONE (SOME(y)) = (SOME(y))
| f2 (SOME(x)) (SOME(y)) = (SOME(x+y))

fun sumOption [] = NONE
| sumOption L = fold f2 NONE (map (fold f2 NONE) L) 

(*
Examples:
> sumOption [[SOME(1),SOME(2),SOME(3)],[SOME(4),SOME(5)],[SOME(6),NONE],[],[NONE]]
SOME 21
> sumOption [[SOME(10),NONE],[SOME(10), SOME(10), SOME(10),NONE,NONE]]
SOME 40
> sumOption [[NONE]]
NONE
> sumOption []
NONE
*)

(*c) sumEither - 15%
returns an IInt value which is the sum of all values in all sublists of the input list. 
The parameter of the IString values should be converted to integer and included in the sum.
The type of the sumEither function should be either list list -> either*)

datatype either = IString of string | IInt of int

fun str2int s = valOf(Int.fromString(s))

fun f3 (IString(s)) (IInt(x)) = (IInt((str2int s) + x))
| f3 (IInt(x)) (IString(s)) = (IInt((str2int s) + x))
| f3 (IString(s)) (IString(t)) = (IInt((str2int s) + (str2int t)))
| f3 (IInt(x)) (IInt(y)) = (IInt(x + y))

fun sumEither [] = IInt(0)
| sumEither L = fold f3 (IInt(0)) (map (fold f3 (IInt(0))) L) 

(*
Examples:
> sumEither [[IString "1",IInt 2,IInt 3],[IString "4",IInt 5],[IInt 6,IString "7"],[],[IString "8"]]
IInt 36
> sumEither [[IString "10" , IInt 10],[],[IString "10"],[]]
IInt 30
> sumEither [[]]
IInt 0
*)

(*5). depthScan, depthSearch, addTrees
(a) depthScan - 10%
returns a list of the ‘a values stored in the leaves and the nodes. 
The order should be the depth-first post-order traversal of the tree.
The type of the depthScan function should be 'a Tree -> 'a list*)

datatype 'a Tree = LEAF of 'a | NODE of 'a * ('a Tree) * ('a Tree)

fun depthScan (LEAF x) = [x]
|depthScan (NODE (x, y, z)) = ((depthScan y)@((depthScan z)@[x]))

(*
Examples:
> depthScan ( NODE("Science",NODE ("and",LEAF "School", NODE("Engineering", LEAF "of",LEAF "Electrical")),LEAF "Computer"))
["School","of","Electrical","Engineering","and","Computer","Science"]
> depthScan (NODE(1, NODE (2, NODE(3, LEAF 4 ,LEAF 5),LEAF 6), NODE(7,LEAF 8,LEAF 9)))
[4,5,3,6,2,8,9,7,1]
> depthScan (LEAF 4)
[4]
*)

(*b) depthSearch – 15%
Write a function depthSearch takes a tree of type 'a Tree and an ‘a value and returns the level of
the tree where the value is found. If the value doesn’t exist in the tree, it returns ~1. The tree nodes
should be visited with depth-first post-order traversal and the level of the first matching node should be
returned. The type of the depthSearch function should be: ''a Tree -> ''a -> int*)

fun depthSearch T tar = 
let 
  fun depthSearchSub (LEAF x) tar level = if x = tar then level else ~1
  | depthSearchSub (NODE (x, y, z)) tar level
    = if (depthSearchSub y tar (level + 1)) <> ~1 then (depthSearchSub y tar (level + 1)) else
      if (depthSearchSub z tar (level + 1)) <> ~1 then (depthSearchSub z tar (level + 1)) else
      ~1
in
  depthSearchSub T tar 1
end;

(*
Examples:
> val myT = NODE(1, NODE (2, NODE(3, LEAF 2 ,LEAF 5),LEAF 1), NODE(1,LEAF 8,LEAF 5))
> depthSearch myT 1
3
> depthSearch myT 5
4
> depthSearch myT 8
3
> depthSearch myT 4
~1
*)

(*c) addTrees – 15%
returns an int Tree where the corresponding nodes from the two trees are added. 
The type of the addTrees function should be int Tree -> int Tree -> int Tree*)

  fun addTrees (LEAF(u)) (LEAF(v)) = LEAF(u + v)
  | addTrees (LEAF(u)) (NODE(v, w, x)) = NODE(u + v, w, x)
  | addTrees (NODE(v, w, x)) (LEAF(u))  = NODE(u + v, w, x)
  | addTrees (NODE(s, t, u)) (NODE(v, w, x)) = NODE(s + v, (addTrees t w), (addTrees u  x))

(*
Examples:
val T1 = NODE(1, NODE (2, NODE(3, (LEAF 4) ,(LEAF 5)),(LEAF 6)), NODE(7,(LEAF 8),(LEAF 9)))
val T2 = NODE(1, NODE (2, LEAF 3, LEAF 6), NODE(7, NODE(8, LEAF 10 ,LEAF 11),LEAF 9))
And addTrees T1 T2 will return the rightmost int Tree which is equivalent to the following:
NODE (2,NODE (4,NODE (6,LEAF 4,LEAF 5),LEAF 12), NODE (14,NODE (16,LEAF 10,LEAF 11),LEAF 18))
*)