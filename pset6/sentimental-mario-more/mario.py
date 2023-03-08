# TODO
from cs50 import get_int


# Def main F
def main():

    height = 0
    while height < 1 or height > 8:
        height = get_int("Height: ")

    draw(height)


# Def draw F
def draw(n):

    # Print rows of height 1 to n...
    for i in range(1, n + 1):
        # ... that are i-1 spaces, i hashes, 2 spaces, i hashes
        print((" " * (n-i)) + ("#" * i) + "  " + ("#" * i))


# Execute
main()