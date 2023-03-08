# Without cs50

def main():
    height = get_height()
    for i in range(height):
        print("?" * height)

def get_height():
    while True:
        try:
            n = int(input("Height: "))
        except ValueError:
            print("Not an integer!")
        else:
            if n > 0:
                return n


main()