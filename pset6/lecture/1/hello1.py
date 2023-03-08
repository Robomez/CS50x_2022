from cs50 import get_string

answer = get_string("What's your name? ")
# Formatted string prints in {}, concatenation(+) doesn't add spaces comma in print function adds them automatically
print(f"Hello, {answer} " + answer, answer)