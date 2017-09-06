# Hangman game
#

# -----------------------------------
# Helper code
# You don't need to understand this helper code,
# but you will have to know how to use the functions
# (so be sure to read the docstrings!)

import random

WORDLIST_FILENAME = "words.txt"

def loadWords():
    """
    Returns a list of valid words. Words are strings of lowercase letters.
    
    Depending on the size of the word list, this function may
    take a while to finish.
    """
    print("Loading word list from file...")
    # inFile: file
    inFile = open(WORDLIST_FILENAME, 'r')
    # line: string
    line = inFile.readline()
    # wordlist: list of strings
    wordlist = line.split()
    print("  ", len(wordlist), "words loaded.")
    return wordlist

def chooseWord(wordlist):
    """
    wordlist (list): list of words (strings)

    Returns a word from wordlist at random
    """
    return random.choice(wordlist)

# end of helper code
# -----------------------------------

# Load the list of words into the variable wordlist
# so that it can be accessed from anywhere in the program
wordlist = loadWords()

def isWordGuessed(secretWord, lettersGuessed):
    '''
    secretWord: string, the word the user is guessing
    lettersGuessed: list, what letters have been guessed so far
    returns: boolean, True if all the letters of secretWord are in lettersGuessed;
      False otherwise
    '''
    count =0
    for i in range(len(secretWord)):
        if secretWord[i] in lettersGuessed:
            count=count+1
    if count == len(secretWord):
        return True
    else: 
        return False


def getGuessedWord(secretWord, lettersGuessed):
    '''
    secretWord: string, the word the user is guessing
    lettersGuessed: list, what letters have been guessed so far
    returns: string, comprised of letters and underscores that represents
      what letters in secretWord have been guessed so far.
    '''
    str1=''
    for i in range (len(secretWord)):
        if secretWord[i] in lettersGuessed:
            str1=str1+secretWord[i]
        else:
            if (i>0) and (str1[i-1] == '_'):
                str1=str1 + " " + "_"
            else:
                str1=str1+' _'
    return str1


def getAvailableLetters(lettersGuessed):
    '''
    lettersGuessed: list, what letters have been guessed so far
    returns: string, comprised of letters that represents what letters have not
      yet been guessed.
    '''
    import string
    alphabet=string.ascii_lowercase
    str1=''
    for j in range(0,len(lettersGuessed)):
        for i in range (0,len(alphabet)):
            if alphabet[i]!=lettersGuessed[j]:
                str1=str1+alphabet[i]
        alphabet=str1
        str1=''
    return alphabet


def hangman(secretWord):
    '''
    secretWord: string, the secret word to guess.

    Starts up an interactive game of Hangman.

    * At the start of the game, let the user know how many 
      letters the secretWord contains.

    * Ask the user to supply one guess (i.e. letter) per round.

    * The user should receive feedback immediately after each guess 
      about whether their guess appears in the computers word.

    * After each round, you should also display to the user the 
      partially guessed word so far, as well as letters that the 
      user has not yet guessed.

    Follows the other limitations detailed in the problem write-up.
    '''
    lenWord=len(secretWord)
    print("Welcome to the game, Hangman!")
    print ("I am thinking of a word that is " + str(lenWord)+" letters long.")
    print("-----------")
    mistakesMade=0
    guess=8
    count=0
    lettersGuessed=""
    str2=""
    while guess>0:
        flag=True
        count=0
        print("You have " + str(guess)+ " guesses left.")
        print("Available letters:" + getAvailableLetters(lettersGuessed))
        temp=input("Please guess a letter:")
        lettersGuessed=lettersGuessed+str(temp)
        str1=getGuessedWord(secretWord, lettersGuessed)
        for i in range(len(lettersGuessed)-1):
            if lettersGuessed[i]==lettersGuessed[len(lettersGuessed)-1] and len(lettersGuessed)>0:
                print("Oops! You've already guessed that letter: " + str1)
                flag=False
                guess=guess+1
                break
            
        if flag:
            for i in range (len(secretWord)):
                if (secretWord[i]==lettersGuessed[len(lettersGuessed)-1]):
                    print("Good guess: " + str1) 
                    guess=guess+1
                    break
                else:
                    count=count+1
            
            if count==len(secretWord):    
                print("Oops! That letter is not in my word:" + str1) 
        str2=str1
        guess=guess-1
        print("-----------")
        if isWordGuessed(secretWord, lettersGuessed):
            print("Congratulations, you won!")
            break
    won = isWordGuessed(secretWord, lettersGuessed)
    if won == False:
        print("Sorry, you ran out of guesses. The word was " + secretWord +".")
        
        

secretWord=chooseWord(wordlist)
hangman(secretWord)




# When you've completed your hangman function, uncomment these two lines
# and run this file to test! (hint: you might want to pick your own
# secretWord while you're testing)

# secretWord = chooseWord(wordlist).lower()
# hangman(secretWord)
