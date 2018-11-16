class Book

def initialize
  @title = ''
  @author = ''
  @format = ''
  @weight = ''
  @pages = ''
end

def title=(title)
  smallWords = ['and', 'an', 'a','in', 'of', 'over', 'the']
  title =(title.split(' ').each { |word| !smallWords.include?(word) ? word.capitalize! : word }).join(' ')
  title[0] = title[0].upcase
  @title = title
end

def title
  @title
end

end
