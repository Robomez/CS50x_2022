# Meow with a helper get_height()
# Without cs50
# Catching exceptions

def main():
    height = get_height()
    for i in range(height):
        print("#", end="")
    print()


def get_height():
    while True:
        try:
            n = int(input("Height: "))
        except ValueError:
            print("Not an integer!")
# Try/except has else option. Some say it's better to try only one line. Others think it's OK to try couple of lines that are mathematically non necessary to try
        else:
            if n > 0:
                return n


main()