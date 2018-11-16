
class Temperature

  def initialize(givenTemp)
    @givenTemp = givenTemp
  end

  def self.from_fahrenheit (fahrenheit)
    Temperature.new({:f => fahrenheit})
  end

  def self.from_celsius (celsius)
    Temperature.new({:c => celsius})
  end

  def in_fahrenheit
    if @givenTemp[:f] != nil
      @givenTemp[:f]
    else
      (@givenTemp[:c] * 9/5.0) + 32
    end
  end

  def in_celsius
    if @givenTemp[:c] != nil
      @givenTemp[:c]
    else
      (@givenTemp[:f] - 32.0) * 5/9
    end
  end
end

class Celsius < Temperature
  def initialize(temp)
    @givenTemp = {:c => temp}
  end
end

class Fahrenheit < Temperature
  def initialize(temp)
    @givenTemp = {:f => temp}
  end
end
