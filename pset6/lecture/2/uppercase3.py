# Uppercase string all at once. Don't even need an 'after' variable
from cs50 import get_string

before = get_string("Say something ")
print(f"After: {before.upper()}")