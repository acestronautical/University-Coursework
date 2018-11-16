# def before
# end

def measure (numTimes = 1)
  totalElapsed = 0
  for i in 1..numTimes
    startTime = Time.now
    yield
    endTime = Time.now
    elapsedTime = endTime - startTime
    totalElapsed += elapsedTime
  end
  averageElapsed = totalElapsed / numTimes

  return averageElapsed
end
