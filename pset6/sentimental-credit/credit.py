# TODO
from cs50 import get_string
import re


def main():
    number = get_string("What's your credit number? ")
    if checksum(number) == False:
        print("INVALID")
        quit()
    else:
        print('checksum ok')

    if numbers(number) == 'visa':
        print('VISA')
    elif numbers(number) == "mc":
        print('MASTERCARD')
    elif numbers(number) == 'amex':
        print('AMEX')
    else:
        print('INVALID')


# Check length and first numbers
def numbers(number):
    if re.search("^3(?:4|7).{13}$", number):
        return "amex"
    elif re.search("^5[1-5].{14}$", number):
        return "mc"
    elif re.search("^4.{12}$", number) or re.search("^4.{15}$", number):
        return "visa"


# Checksum
def checksum(number):
    sum = 0
    leng = len(number)

    # If number of digits is even
    for i in (range(leng - 1, 0, -2)):
        # Odd digits from last
        sum += int(number[i])

        # Even digits from last
        sraka = int(number[i - 1]) * 2
        if (sraka) > 9:
            zhopa = (sraka) % 10 + (sraka) // 10
            sum += zhopa
        else:
            sum += sraka

    # If number of digits is uneven we add one digit
    if leng % 2 != 0:
        # get last number in the array
        sum += int(number[0])

    # Test if checksum is alright
    if sum % 10 == 0:
        return True
    else:
        return False


main()