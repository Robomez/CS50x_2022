# Logical operators using regular expressions (re)

import re

from cs50 import get_string

s = get_string('Do you agree? ')

# ^ start of input
# & end of input
# . any character
# .* 0 or more characters
# .+ 1 or more characters
# ? optional (in parentheses)

if re.search('^y(es)?$', s, re.IGNORECASE):
    print('Agreed')
elif re.search('^n(o)?$', s, re.IGNORECASE):
    print('Not agreed')