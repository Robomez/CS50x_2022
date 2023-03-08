# Exit with explicit value, import sys as a whole

import sys

if len(sys.argv) != 2:
    print('Only one CLI')
    sys.exit(1)

print(f"hello, {sys.argv[1]}")
sys.exit(0)