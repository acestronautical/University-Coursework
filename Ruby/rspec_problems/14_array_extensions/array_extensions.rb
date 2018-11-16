class Array

  def sum
    self.inject(0) {|sum, num| sum += num}
  end

  def square
    self.map {|num| num * num }
  end

  def square!
    self.map! {|num| num * num }
  end

end
