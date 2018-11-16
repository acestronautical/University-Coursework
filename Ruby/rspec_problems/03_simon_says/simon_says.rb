def echo(string)
  return string
end

def shout(string)
  return(string.upcase)
end

def repeat(string, times = 2)
  return((Array.new(times + 1)).join(string + ' ')[0..-2])
end

def start_of_word(string, howMany)
  string[0..(howMany - 1)]
end

def first_word(string)
  string.split(' ')[0]
end

def titleize(string)
    smallWords = ['and', 'over', 'the']
    caps =(string.split(' ').each { |word| !smallWords.include?(word) ? word.capitalize! : word }).join(' ')
    caps[0] = caps[0].upcase
    return(caps)
end
