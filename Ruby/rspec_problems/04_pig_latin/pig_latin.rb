def translate(string)
  vouls = ['a', 'e', 'i', 'o', 'u']
  pigLatin = string.split(' ')
  idx = 0
  while idx < pigLatin.length
    word = pigLatin[idx]
    numCons = 0
    while !vouls.include?(word[numCons])
      numCons += 1
    end
      if numCons == 0
        pigLatin[idx] += 'ay'
      else
        if word[0..(numCons + 1)].include?('qu')
          numCons += 1
        end
        word = word[(numCons)..-1] + word[0..(numCons - 1)]
        pigLatin[idx] = word + 'ay'
      end
      idx += 1
  end
  pigLatin = pigLatin.join(' ')
  return(pigLatin)
end
