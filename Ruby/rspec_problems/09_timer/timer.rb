class Timer

  def initialize
    @seconds = 0
  end

  def seconds=(seconds)
    @seconds = seconds
  end

  def seconds
    @seconds
  end

  def time_string
    seconds = @seconds
    hours = (seconds / 3600).to_s.rjust(2,'0')
    seconds = (seconds % 3600)
    minutes = (seconds / 60).to_s.rjust(2,'0')
    seconds = (seconds % 60).to_s.rjust(2,'0')
    return(hours + ':' + minutes + ':' + seconds)
  end


end
