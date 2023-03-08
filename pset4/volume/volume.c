// Modifies the volume of an audio file

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

// Number of bytes in .wav header
const int HEADER_SIZE = 44;

int main(int argc, char *argv[])
{
    // Check command-line arguments
    if (argc != 4)
    {
        printf("Usage: ./volume input.wav output.wav factor\n");
        return 1;
    }

    // Open files and determine scaling factor
    FILE *input = fopen(argv[1], "r");
    if (input == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }

    FILE *output = fopen(argv[2], "w");
    if (output == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }

    float factor = atof(argv[3]);

    // TODO: Copy header from input file to output file
    // Array named header, each element is uint8_t(1 byte)
    uint8_t header[HEADER_SIZE];

    // These 2 versions of argument have the same result, but different inside.
    // The first one is maybe faster, as it's O(1), second one is probably O(n)
    // First one takes in the whole header once
    fread(header, HEADER_SIZE, 1, input);
    // Second one takes in a byte and reads it HEADER_SIZE times
    fwrite(header, sizeof(uint8_t), HEADER_SIZE, output);

    // TODO: Read samples from input file and write updated data to output file
    // Variable buffer
    int16_t buffer;
    while (fread(&buffer, sizeof(int16_t), 1, input) == 1)
    {
        buffer = buffer * factor;
        fwrite(&buffer, sizeof(int16_t), 1, output);
    }

    // Close files
    fclose(input);
    fclose(output);
}
