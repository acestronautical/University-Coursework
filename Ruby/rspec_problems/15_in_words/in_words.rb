class Fixnum
  def in_words()
    num = self.to_s.reverse
    digitCount = num.length
    ones = {1 =>'one', 2 =>'two',3 =>'three',4 =>'four',5 =>'five',6 =>'six',7 =>'seven',8 =>'eight',9 =>'nine'}
    teens = {10 => 'ten',11 => 'eleven',12 => 'twelve',13 => 'thirteen',14 => 'fourteen',15 => 'fifteen',16 => 'sixteen',17 => 'seventeen',18 => 'eighteen',19 => 'nineteen'}
    tens = {2 => 'twenty',3 => 'thirty',4 => 'forty',5 => 'fifty',6 => 'sixty',7 => 'seventy',8 => 'eighty',9 => 'ninety'}
    if num == /00+/.match(num).to_s
      return ''
    elsif digitCount == 1 && num != '0'
      return ones[num.to_i]
    elsif digitCount == 2 && num[1] == '1'
      return teens[num.reverse.to_i]
    elsif digitCount == 2 && num[0] == '0'
      return tens[num[1].to_i]
    elsif digitCount == 2
      return tens[num[1].to_i] +" " + num[0].reverse.to_i.in_words
    elsif num == '0'
      return 'zero'
    elsif digitCount == 3 && num[0..-2] == '00'
      return ones[num[2].to_i] + " hundred"
    elsif digitCount == 3
      return ones[num[2].to_i] + " hundred " + num[0..-2].reverse.to_i.in_words
    elsif digitCount == 4 && num[0..-2] == '000'
      return ones[num[3].to_i] + " thousand"
    elsif digitCount == 4
      return ones[num[3].to_i] + " thousand " + num[0..-2].reverse.to_i.in_words
    elsif digitCount == 5
      return num[3..4].reverse.to_i.in_words + " thousand " + num[0..2].reverse.to_i.in_words
    elsif digitCount == 6
      return num[3..5].reverse.to_i.in_words + " thousand " + num[0..2].reverse.to_i.in_words
    elsif digitCount == 7  && num[0..-2] == '000000'
      return ones[num[6].to_i] + " million"
    elsif digitCount == 7
      return ones[num[6].to_i] + " million " + num[0..5].reverse.to_i.in_words
    elsif digitCount == 8
      return num[6..7].reverse.to_i.in_words + " million " + num[0..5].reverse.to_i.in_words
    elsif digitCount == 9
      return num[6..8].reverse.to_i.in_words + " million " + num[0..5].reverse.to_i.in_words
    elsif digitCount == 10  && num[0..-2] == '000000000'
      return ones[num[9].to_i] + " billion"
    elsif digitCount == 10
      return ones[num[9].to_i] + " billion " + num[0..8].reverse.to_i.in_words
    elsif digitCount == 11
      return num[9..10].reverse.to_i.in_words + " billion " + num[0..8].reverse.to_i.in_words
    elsif digitCount == 12
      return num[9..11].reverse.to_i.in_words + " billion " + num[0..8].reverse.to_i.in_words
    elsif digitCount == 13  && num[0..-2] == '000000000000'
      return ones[num[12].to_i] + " trillion"
    elsif digitCount == 13
      return ones[num[12].to_i] + " trillion " + num[0..11].reverse.to_i.in_words
    elsif digitCount == 14
      return num[12..13].reverse.to_i.in_words + " trillion " + num[0..11].reverse.to_i.in_words
    elsif digitCount == 15
      return num[12..13].reverse.to_i.in_words + " trillion " + num[0..11].reverse.to_i.in_words
    end
  end
end
