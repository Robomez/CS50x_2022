 #include <cs50.h>
#include <stdio.h>

int main(void)
{

    long number = 0;

    // Prompt to type in a credit card number
    do
    {
        number = get_long("What's your credit card number (without spaces)? ");
    }
    while (number < 1);

    // Calculate the checksum and get number length
    long num = number;
    int length = 0;
    int checksum = 0;
    int remainder = 0;

    do
    {
        remainder = num % 10;
        // Add every other digit form 1st right to checksum
        if (length % 2 == 0)
        {
            checksum = checksum + remainder;
        }
        // Add summarized digits of (every other digit form 2nd right * 2) to checksum
        // If (every other digit form 2nd right * 2) < 10 then it adds number + 0, no need for other conditional
        else
        {
            checksum = checksum + remainder * 2 / 10 + remainder * 2 % 10;
        }
        num = num / 10;
        length++;
    }
    while (num > 0);

    // Decide whether it's a valid card or not
    // Get first 2 digits
    long digits = number;
    
    do
    {
        digits = digits / 10;
    }
    while (digits > 100);

    // Check checksum last digit
    if (checksum % 10 == 0)
    {
        // If amex
        if ((digits == 34 || digits == 37) && length == 15)
        {
            printf("AMEX\n");
        }
        // Else if master
        else if ((digits > 50 && digits < 56) && length == 16)
        {
            printf("MASTERCARD\n");
        }
        // Else if visa
        else if ((length == 13 || length == 16) && digits / 10 == 4)
        {
            printf("VISA\n");
        }
        //else when checksum last digit is 0
        else
        {
            printf("INVALID\n");
        }
    }
    // If checksum lasst digit isn't 0
    else
    {
        printf("INVALID\n");
    }
}