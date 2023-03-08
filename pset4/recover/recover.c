#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef uint8_t BYTE;

const int BLOCK_SIZE = 512;

int main(int argc, char *argv[])
{
    // Accept one argument - the name of a forensic image from which to recover JPEGs
    // If not, return 1 and remind user of correct usage
    if (argc != 2)
    {
        printf("Print only one argument that is a filename\n");
        return 1;
    }

    // Open memory card
    // If image cannot be opened for reading, return 1 and inform user
    char *raw_file = argv[1];

    FILE *input = fopen(raw_file, "r");
    if (input == NULL)
    {
        printf("Could not open %s.\n", raw_file);
        return 1;
    }

    // Buffer for storing and writing
    BYTE *buffer = malloc(BLOCK_SIZE);

    // New image count
    int number = 0;

    // A string for a filename
    char *filename = malloc(8);
    sprintf(filename, "%03i.jpg", number);
    FILE *name = fopen(filename, "w");
    if (name == NULL)
    {
        printf("Could not open %s.\n", raw_file);
        return 1;
    }

    // If fread returns less then 255, then it's the end of the file
    while (fread(buffer, 1, BLOCK_SIZE, input) == BLOCK_SIZE)
    {

        // Look for a beginning of a JPEG
        // First 4 bytes 0xff 0xd8 0xff 0xe0-0xef
        // Bitwise arithmetic
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
            // If first JPEG
            if (number == 0)
            {
                // Open a new JPEG file
                // Generated files should be named ###.jpg, where ### is a three-digit decimal number, starting with 000
                fwrite(buffer, 1, BLOCK_SIZE, name);
                number++;
            }
            else
            {
                fclose(name);
                sprintf(filename, "%03i.jpg", number);
                name = fopen(filename, "w");
                fwrite(buffer, 1, BLOCK_SIZE, name);
                number++;
            }
        }
        else
        {
            // If not a JPEG, continue searching
            if (number == 0)
            {
                continue;
            }
            // If middle of JPEG, continue writing
            else
            {
                fwrite(buffer, 1, BLOCK_SIZE, name);
            }
        }
    }

    fclose(name);
    fclose(input);

    // Valgrind if malloc
    free(buffer);
    free(filename);

    return 0;
}