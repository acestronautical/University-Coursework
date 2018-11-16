class Dictionary
  def initialize
    @entries = {}
  end

  def entries
    @entries
  end

  def add(item)
    case item
    when {}.class
      @entries.merge!(item)
    when ''.class
      @entries.merge!({item => nil})
    when 1.class
      @entries.merge!({item.to_s => nil})
    else
      puts 'item type error'
    end
  end

  def keywords
    @entries.keys.sort
  end

  def include?(item)
    @entries.has_key?(item)
  end

  def find(item)
    found = {}
    @entries.each_key{ |key| key[0..item.length - 1].include?(item) ? found.merge!({key => @entries[key]}) : key }
    return found
  end

  def printable
    printString = ''
    Hash[@entries.sort].each_key{ |key| printString += "\n[" + key + "] " + "\"" + @entries[key] + "\"" }
    printString.slice!(0)
    return printString

  end

end
