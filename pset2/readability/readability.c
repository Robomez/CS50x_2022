#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

int count_letters(string text);
int count_words(string text);
int count_sentences(string text);

int main(void)
{
    // Prompt user for a string using get_string
    string text = get_string("Put some text here: ");

    // Count the number of letters, words, and sentences in the text
    int letters = count_letters(text);
    // printf("%i letters\n", letters);
    int words = count_words(text);
    // printf("%i words\n", words);
    int sentences = count_sentences(text);
    // printf("%i sentences\n", sentences);

    // Output "Grade X" where x is grade level computed by formula, rounded to a nearest int.
    double letters_average = ((double) letters / (double) words) * 100;
    double sentences_average = ((double) sentences / (double) words) * 100;
    double index = (0.0588 * letters_average) - (0.296 * sentences_average) - 15.8;
    // printf ("Index is %f\n", index);
    // If number is 16 or higher, output should be "Grade 16+"
    if (index >= 16)
    {
        printf("Grade 16+\n");
    }
    // If the index number is less than 1, your program should output "Before Grade 1".
    else if (index < 1)
    {
        printf("Before Grade 1\n");
    }
    else
    {
        printf("Grade %i\n", (int) round(index));
    }
}

// Count the number of letters
int count_letters(string text)
{
    int letter_count = 0;
    // A letter is a character of lower- or uppercase from a to z
    for (int i = 0, l = strlen(text); i < l; i++)
    {
        text[i] = toupper(text[i]);
        if (text[i] > 64 && text[i] < 91)
        {
            letter_count++;
        }
    }
    return letter_count;
}

int count_words(string text)
{
    int word_count = 1;
    for (int i = 0, l = strlen(text); i < l; i++)
    {
        if (text[i] == 32)
        {
            word_count++;
        }
    }
    // Seq of chars separated by space is a word
    return word_count;
}

int count_sentences(string text)
{
    int sentences_count = 0;
    for (int i = 0, l = strlen(text); i < l; i++)
    {
        // If a . , ? or ! appears, then it's the end of a sentence.
        if (text[i] == 33 || text[i] == 46 || text[i] == 63)
        {
            sentences_count++;
        }
    }
    return sentences_count;
}
