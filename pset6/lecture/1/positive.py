from cs50 import get_int

def main():
    i = get_positive_int();
    print(i)


def get_positive_int():
    while True:
        try:
            n = int(input("Positive integer: "))
            if (n > 0):
                break
        except ValueError:
            print('Not an integer')
    return n


main()