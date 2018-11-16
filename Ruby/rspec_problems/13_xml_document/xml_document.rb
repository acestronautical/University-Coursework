class XmlDocument

  def initialize(boolean = false)
    @indent = boolean
    @spaces = ""
  end

  def generate(hash, tag)
    propValPairs = ''
    @spaces = @spaces + "\s\s"
    spaces = @spaces
    hash.each_key { |key| propValPairs += (" " + key.to_s + "='" + hash[key] + "'")}
    if block_given? && @indent
      return (spaces.sub("\s\s", "")) + "<" + tag + ""+ propValPairs +">\n" + yield + (spaces.sub("\s\s", "")) + "</" + tag + ">\n"
    elsif block_given?
      return "<" + tag + ""+ propValPairs +">" + yield + "</" + tag + ">"
    elsif @indent
      @spaces = ""
      return (spaces.sub("\s\s", "")) + "<" + tag + ""+ propValPairs +"/>\n"
    else
      return "<" + tag + ""+ propValPairs +"/>"
    end
  end

  def hello (hash = {},  &block)
    tag = 'hello'
    generate(hash, tag, &block)
  end

  def goodbye (hash = {}, &block)
    tag = 'goodbye'
    generate(hash, tag, &block)
  end

  def ok_fine (hash = {}, &block)
    tag = 'ok_fine'
    generate(hash, tag, &block)
  end

  def come_back (hash = {}, &block)
    tag = 'come_back'
    generate(hash, tag, &block)
  end

  def send (tag_name)
    return ("<#{tag_name}/>")
  end

end
