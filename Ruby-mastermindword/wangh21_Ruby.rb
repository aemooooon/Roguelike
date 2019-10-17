##############################################
##############################################
##### 2019 S1 Programming 4 Assignment 2 #####
##### Ruby Mastermind word game          #####
##### Studnet name: Hua Wang             #####
##### Lecturer name: Grayson             #####
##### Date: 2019-06-15                   #####
##############################################
##############################################

# I am not good at English, So I am not sure how much grammar or vocabulary I have got wrong.
# So I just put my diary log of Ruby Learning link here as my self-study evidence
# https://github.com/aemooooon/puppet/wiki/Ruby

# Define two constants
# N_ROUNDS is a Integer which how many times player can guess
N_ROUNDS = 10
# SLEEP_TIME just as a argument to sleep() method
SLEEP_TIME = 0.37

# Define a global Array variable dictionary to store all words read from the file
# There is not necessary to use @variable, I just wanna show more knowledge
@dictionary = Array.new

=begin
The Word class includes all operation of word, it have four method
The read_words method reads all words from mastermindWordList.txt file and return a Array
The check_duplicate_letter method is going to check the word which is duplicated with each letter
The filter_invalid_word method will check each word whether valid such as not 5 letter, 
each letter occur two times in one word and other invalid chars before put to Array
The get_random_word method will generate a word which grab by randomly index, the random range 
from 0 to the length of word Array
=end
class Word
  # This method reads all words from file named "mastermindWordList.txt" and return this words Array
  def read_words()
    # Define an empty array
    results=Array.new
    # Define a file which holds a branch of word
    file_path="mastermindWordList.txt";
    # Check the file whether exists
    if File::exists?(file_path)
      # open the file in read mode if the file exists
      file = File.open(file_path, "r") do |f|
        # loop all file record
        f.each_line do |word|
          # call filter_invalid_dord method to check each of the word
          # thie check will reject all not 5 letters, letter duplicate and includes non-alphabet word
          if(filter_invalid_word(word))
            # push the each word that has already checked to Array
            # the << operator just like Array.push method
            # chomp method will take out off \r \n
            # downcase method change letter to lowercase
            results << word.chomp.downcase
          end
        end # end of the for each loop
      end
      # call file.close method to release resources when file content readed over
      file.close
    else
      # Give player an feedback if the file does not exists
      puts "The word list file is not exists."
      return
    end
    # return an array to the method
    return results
  end

  # This method will filter out all the words with duplicate letters in the word list Array.
  def check_duplicate_letter(words)
    # The reject method return a new Array without the items defined by its input block.
    return words.reject {
      # The word has each letter counted .chars .count
      # If the word with any repeating characters removed is not the same as the length of the word
      # The uniq method returns a new array by removing duplicate values in self.
      |word| word.chars.uniq.count != word.length
    }
  end

  # The filter_invalid_word method accept a single word as argument
  # The filter_invalid_word method return a bool value
  def filter_invalid_word(word)
    # Define a string which includes all valid letter
    letters = "abcdefghijklmnopqrstuvwxyz"
    # Define return variable and give a default value
    valid = true
    # transfer the word to lowercase and take out off \r\n
    word = word.chomp.downcase
    # set return value as false if the length of word not exactly equal 5
    if (word.split(//).size != 5)
        valid = false
    end
    # loop each word
    word.split(//).each do |letter|
        # If the letter occurs more than once in the word, set return value to false
        if (word.count(letter.to_s)) > 1 
            valid = false
        end
        # If the letter does not included in valid letter, set return value to false
        if (letters.include?(letter) == false) 
            valid = false
        end
    end
    # return a bool value to method
    return valid
  end

  # The method accept an array as argument
  # The method return a single word
  # This method generates a random number between 0 and the lenght of the word Array. 
  # Its return a word stored in the word Array at the randomly generated index.
  def get_random_word(words)
    # rand method with an integer argument (the length of words) get a new integer between 0 & the length of words
    return words[rand(words.count)]
  end

end # end of the Word class

=begin
The Game class defines all operation about Game which includes 4 methods and 1 attribute member
The attr_accessor word will be stored word that by Word class generate a random word
The instruction method just simple display instruction to player
The check_player_words will compare to player input word and system random generate word
The check_input method will check the player input word whether valid
The run method is main game flow, keep tracking of player playing.
=end
class Game
  # Defines a named attribute word to Game class for instance of Game to call
  attr_accessor :word

  # Thie method just simply show the instruction of rules of the game
  def instruction()
    puts "Welcome to the MasterMind word game"
    puts "\nThe System has been generate a word which includes 5 letters and no duplicate each \nletter, you are going to guess this word. you have 10 times chance to guess. you \nwill get a feedback in each turn like below: \n\n Exact: The letter is an exact match to the letter in the same position in the code\n Near:  The letter is contained in the code, but is not in the correct position\n Miss:  The letter is not contained in the code\n"
  end

  # This method accept a word as argument
  # use loop to compare each letter whether equal between guess word and random word
  # the each_with_index can get both value and index
  # if the guess letter is an exact match to the random letter in the same postion, print Exact
  # if the guess letter is contained int the random word without correct postion, print Near
  # if the guess letter is not contained int the random word, print Miss
  # to_s method that convert object to string type
  def check_player_words(player_guess_word)
    word.chomp.chars.each_with_index{
      |item, index|
      if item == player_guess_word.chomp.chars[index].to_s # exactly equal and in the same postion
        result = "Exact"
      elsif word.chomp.include?(player_guess_word.chars[index].to_s) # just includes the letter
        result = "Near"
      else # other condition that either not exact nor includes is.
        result = "Miss"
      end
      sleep(SLEEP_TIME) # just stop for a time make a good user experience
      puts "Letter: #{player_guess_word.chars[index]} : #{result}"
    }
  end # end of check_player_words method

  def check_input(input_word)
    # Define a string which includes all valid letter
    dict = "abcdefghijklmnopqrstuvwxyz"
    # Define return variable and give a default value
    is_valid = true
    # set return value as false if the length of word not exactly equal 5
    if(input_word.split(//).size != 5)
      is_valid = false
    end
    # If the letter occurs more than once in the word, set return value to false
    # include? method to find if a letter is included in input_word
    input_word.split(//).each do |letter|
      if(dict.include?(letter) == false)
        is_valid = false
      end
    end # end of the each method
    return is_valid
  end

  # This method accept a integer type value as argument which is defined as CONSTANTS
  # This method to control player playing flow
  # Its includes two local variable one Integer for guess times, one bool for whether guess correct or not
  def run(n_rounds)
    # Define a Integer type variable make the default as 0
    guess_count = 0
    # Define a bool type variable make the default as false when at the start of the game
    is_guessed = false
    # until loop (the end of the condition is guess_count equal total times or the player guess correct)
    # or keyword just like || token, [and, or, not] = [&&, ||, !]
    until guess_count == n_rounds or is_guessed
      # on the top of screen, tell the player how many times guess has left
      puts "\nYou have left #{n_rounds - guess_count} times chances.\n"
      # ask player a input about guess content
      puts "\nType the word you guess: "
      # get the player type value take off the space and convert to lowercase then assign variable input_word
      input_word=gets.chomp.downcase.strip
      # call check_input method to check the player type whether Invalid
      if(!check_input(input_word))
        puts "\nInvalid word, please try again :-("
      else
        # if get valid type, count the times
        guess_count += 1
        # also call check_player_words method which is enter each letter check flow
        check_player_words(input_word)
      end
      # if the word of player typeing exactly equal the word of system generated
      # tell player the correct message. and set the flag to true.
      if(word.chomp == input_word.chomp)
        puts "\nCongratulations, you are correct."
        is_guessed = true
      end
    end # end of the until loop    
    # after all check if not guees the correct word
    # gives some feedback to player
    if !is_guessed
      puts "\nSorry, you are out of the chance to guess"
      puts "\nThe word was [#{word.chomp}]"
    end
  end # end of the run method

end  # end of the Game class


=begin
The below section is main calling part, just like main function in C like language
it is main entry of application
=end

# Define the object word as the instantialization of the Word class
word = Word.new
# Define the object game as the instantialization of the Game class
game = Game.new

# clear the history of the command line just keep screen clear
# it can also use system "clear"
system "cls"

# call the instrcution method of Game class
game.instruction()

# call the both of Word method check_duplicate_letter and read_words
# the get the value words list assign to global variable @dictionary
@dictionary = word.check_duplicate_letter(word.read_words())

# this is main playing flow control section
# I use two nested loop begin end while and begin end until
# the internal loop for ask player wanna keep play or exit, also use case keyword just like switch in other language
# the external loop for run the game times which is defined in the constants
begin
  # call the get_random_word method of Word class that get a single word
  # then assign variable random_word
  random_word = word.get_random_word(@dictionary)
  puts "\nGood luck"
  # assign the word to the atrribute of the Game class game.word
  game.word = random_word
  # call the run method of the Game clas
  game.run(N_ROUNDS)
  # ask player whether wanna player one more times
  puts "\nWould you like to play again? "
  # the starting of internal loop
  begin
    # ask player input Y or N
    puts "\nEnter 'Y' or 'N': "
    # accept the input of the player and convert to upcase and filter other char
    selection = gets.chomp.upcase.strip
    # the starting of the case statement which the condition is player input
    case selection
    when "Y" # if the answer is Y then set the bool value as true
      is_done = true
    when "N" # if the answer is N then set the bool value as false, also gives some feedback and exit the game
      is_done = false
      puts "\nThank you, GoodBye"
      exit
    else # if the player not input Y,N or y,n, gives feedback
      puts "\nInvalid input, Please try again"
    end
  end until selection == 'N' || selection == 'Y' # end of the internal loop, the condition is input the Y,N by Player
end while is_done # end of the external loop if the is_done falg equal true
