# TODO

# Comment 1 for style50
def draw(n):
    for i in range(1, n + 1):
        print(" " * (n-i) + "#" * i)


# Comment 2 for style50
while True:
    try:
        height = int(input("Height: "))
    except ValueError:
        print("Need an integer")
    else:
        if height > 0 and height < 9:
            draw(height)
            exit(0)
        else:
            print("Positive integer between 1 and 8")
