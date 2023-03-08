# from cs50 import get_string
# answer = get_string("What's your name? ")

# Input function takes reads a line from input, converts it to a string (stripping a trailing newline),
# and returns that.
answer = input("What's your name? ")

# Formatted string prints in {}, concatenation(+) doesn't add spaces comma in print function adds them automatically
print(f"Hello, {answer}" +" "+ answer, answer)