# Print a command-line argument, index into argv

from sys import argv

for i in range(len(argv)):
    print(argv[i])