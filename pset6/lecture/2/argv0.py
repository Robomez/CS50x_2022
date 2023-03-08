# Print a command-line argument

from sys import argv

if len(argv) == 2:
    print('Hello,', argv[1])
    print(f'Hello, {argv[1]}')
else:
    print('Hello, world')