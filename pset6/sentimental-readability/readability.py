# TODO
from cs50 import get_string

# Get a text string
text = get_string("Paste text here\n")

# Program should count the number of letters, words and sentences in the text.

# Count letters. Up or low case apha chars. Not punctuation, digits or other symbols. Return an int (number of letters).
# Count sentences. They all end with '.' , '!' or '?'
letters = 0
sentences = 0

for letter in text:
    if letter.isalpha():
        letters += 1
    elif ord(letter) in [33, 46, 63]:
        sentences += 1

# Count words. Any sequence pf chars separated by a space. Return in (number of words)
words = len(text.split())


# index = 0.0588 * L - 0.296 * S - 15.8
# L - average number of letters per 100 words in text
# S - average number of sentences per 100 words in text
index = .0588 * (letters / words) * 100 - .296 * (sentences / words) * 100 - 15.8

# print the answer 'Grade X' with print() where X is calc'd and rounded to the nearest integer
# If num is 16 or higher, print 'Grade 16+'. If <1 print 'Before Grade 1'
if index < 1:
    print("Before Grade 1")
elif index >= 16:
    print("Grade 16+")
else:
    print("Grade", round(index))
