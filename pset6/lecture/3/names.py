# Implements linear search for names

import sys

# A list of names
names = ['Ron', 'Bon', 'Jon', "Kon", 'Lon', 'Don']

# Search for Kon
if 'Kon' in names:
    print('Found')
    sys.exit(0)

print('Not found')
sys.exit(1)