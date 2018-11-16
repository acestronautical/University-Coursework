class RPNCalculator
  def initialize
    @value = 0
    @stack = []
    @operandsCheck = Proc.new  {raise("calculator is empty") if @stack.length < 2  }
    @setValue = Proc.new {@value = @stack[-1]}
  end

  def push(num)
    @stack << num
  end

  def plus
    @operandsCheck.call
    @stack.push(@stack.pop.to_f + @stack.pop.to_f)
    @setValue.call
  end

  def times
    @operandsCheck.call
    @stack.push(@stack.pop.to_f * @stack.pop.to_f)
    @setValue.call
  end

  def minus
    @operandsCheck.call
    @stack.push(-(@stack.pop.to_f) + @stack.pop.to_f)
    @setValue.call
  end

  def divide
    @operandsCheck.call
    @stack.push(1 / (@stack.pop.to_f) * @stack.pop.to_f)
    @setValue.call
  end

  def value
    @value
  end


end
