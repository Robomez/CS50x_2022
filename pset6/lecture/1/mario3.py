# Meow with a helper get_height()
# Without cs50

def main():
    height = get_height()

    for i in range(height):
        for j in range(height):
            print("?", end="")
        print()


def get_height():
    while True:
        try:
            n = int(input("Height: "))
            if n > 0:
                return n
        except ValueError:
            print("Not an integer!")
    # return n


main()