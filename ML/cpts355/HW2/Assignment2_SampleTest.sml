 fun partitionTest () =
 let 
	 fun exists n [] = false |  exists n (x::rest) = if n=x then true else (exists n rest)
     val partitionT1 = ( (partition (fn x => (x<=4)) [1,7,4,5,3,8,2,3]) = ([1,4,3,2,3],[7,5,8]) )
     val partitionT2 = ( (partition null [[1,2],[1],[],[5],[],[6,7,8]]) = ([[],[]],[[1,2],[1],[5],[6,7,8]]) )
     val partitionT3 = ( (partition (exists 1) [[1,2],[1],[],[5],[],[6,7,8]]) = ([[1,2],[1]],[[],[5],[],[6,7,8]]) )
 in 
     print ("partition:-------------------- \n   test1: " ^ Bool.toString(partitionT1) ^  "\n" ^
            "   test2: " ^ Bool.toString(partitionT2) ^ "\n" ^ 	
            "   test3: " ^ Bool.toString(partitionT3) ^ "\n")		

end
val _ = partitionTest()