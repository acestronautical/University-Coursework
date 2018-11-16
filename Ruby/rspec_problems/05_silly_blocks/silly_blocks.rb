def reverser
  input = yield
  return (input.split(' ').collect {|word| word.reverse}.join(' '))
end

def adder(num = 1)
  yield + num
end

def repeater(num = 1)
  for i in 1..num
 yield 
 end
end
