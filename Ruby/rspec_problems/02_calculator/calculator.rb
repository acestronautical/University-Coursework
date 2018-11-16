def add (num1, num2)
  num1 + num2
end

def subtract (num1, num2)
  num1 - num2
end

def sum (array)
  sum = 0
  array.each do |num|
    sum += num
  end
  return sum
end

def multiply (array)
  sum = 1
  array.each do |num|
    sum = num * sum
  end
  return sum
end

def power(num, pow)
  idx = 1
  sum = 1
 while idx <= pow
   sum = sum * num
   idx += 1
 end
 return(sum)
end

def factorial(n)
  if n<= 1
    1
  else
    n * factorial( n - 1 )
  end
end
