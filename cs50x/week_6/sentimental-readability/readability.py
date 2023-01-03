from sys import exit
import re
import math

# Collecting user input
answer = input("Text: ")

# Count the number of letters in string -----------------------------------------------------------------------------------------------------------------
# Here I am catching the answer string and replacing every character that is not a letter or number with nothing ''
# Then, im taking the lenght of this newly treated string
# \W means everything thar is not alphan
letters = len(re.sub(r'\W', '', answer))

# Count the number of words in string -------------------------------------------------------------------------------------------------------------------
words = answer.count(' ') + 1

# Check if the last character of the string is a blank space
if answer[len(answer) - 1] == ' ':
    words -= 1

# Check if the first character of the string is a blank space
if answer[0] == ' ':
    words -= 1

# Count the number of sentences in string ----------------------------------------------------------------------------------------------------------------
# Here I am finding all the ,?! present in the answer string using re.findall(r'[things to find]', string_being_used)
# Then I am calculating the total lenght of the newly created string tha contains only the characters I passed as argument r'[things to find]'
sentences = len(re.findall(r'[!?.]', answer))

if sentences == 0:
    sentences = 1

# Calculate Coleman Index -------------------------------------------------------------------------------------------------------------------------------
coleman_index = round(0.0588 * letters / words * 100 - 0.296 * sentences / words * 100 - 15.8)

print(letters, words, sentences, coleman_index)

# CHecking conditions
if coleman_index > 16:
    print("Grade 16+")
    exit(0)

elif coleman_index < 0:
    print("Before Grade 1")
    exit(0)

else:
    print("Grade ", coleman_index)
    exit(0)

