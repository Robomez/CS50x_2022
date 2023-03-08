#include "helpers.h"

#include <math.h>
#include <stdlib.h>
#include <stdio.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    int average = 0;

    // Loop for each row
    for (int i = 0; i < height; i++)
    {
        // Inside each row loop for each pixel
        for (int j = 0; j < width; j++)
        {
            // Calculate an average bgr
            average = round((image[i][j].rgbtBlue + image[i][j].rgbtGreen + image[i][j].rgbtRed) / 3.0);

            // Equalize all color channels
            image[i][j].rgbtBlue = average;
            image[i][j].rgbtGreen = average;
            image[i][j].rgbtRed = average;
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    int sepiaRed = 0, sepiaGreen = 0, sepiaBlue = 0;
    // Loop for each row
    for (int i = 0; i < height; i++)
    {
        // Inside each row loop for each pixel
        for (int j = 0; j < width; j++)
        {
            // Remember channel values must be 0 to 255
            sepiaRed = round(.393 * image[i][j].rgbtRed + .769 * image[i][j].rgbtGreen + .189 * image[i][j].rgbtBlue);
            if (sepiaRed > 255)
            {
                sepiaRed = 255;
            }

            sepiaGreen = round(.349 * image[i][j].rgbtRed + .686 * image[i][j].rgbtGreen + .168 * image[i][j].rgbtBlue);
            if (sepiaGreen > 255)
            {
                sepiaGreen = 255;
            }

            sepiaBlue = round(.272 * image[i][j].rgbtRed + .534 * image[i][j].rgbtGreen + .131 * image[i][j].rgbtBlue);
            if (sepiaBlue > 255)
            {
                sepiaBlue = 255;
            }
            image[i][j].rgbtRed = sepiaRed;
            image[i][j].rgbtGreen = sepiaGreen;
            image[i][j].rgbtBlue = sepiaBlue;
        }
    }

    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{

    // temporary RGBTRIPLE array to copy inverted row
    RGBTRIPLE(*temp_row) [width] = malloc(width * sizeof(RGBTRIPLE));
    if (temp_row == NULL)
    {
        printf("Not enough memory to store row for mirroring.\n");
        return;
    }

    // Loop for each row
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            (*temp_row)[j] = image[i][(width - 1) - j];
        }
        for (int k = 0; k < width; k++)
        {
            image[i][k] = (*temp_row)[k];
        }
    }
    free(temp_row);
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{

    // We need temporary int before dividing the sum, becuase tmp_im[i][j].rgbtRed can't be more than 255
    int temp = 0;
    // Temporary image array to store blured image
    RGBTRIPLE(*tmp_im)[width] = calloc(height, width * sizeof(RGBTRIPLE));
    if (tmp_im == NULL)
    {
        printf("Not enough memory to store image for blurring.\n");
        return;
    }

    // First row
    // First pixel
    temp = image[0][0].rgbtRed + image[0][1].rgbtRed + image[1][0].rgbtRed + image[1][1].rgbtRed;
    tmp_im[0][0].rgbtRed = round(temp / 4.0);

    temp = image[0][0].rgbtGreen + image[0][1].rgbtGreen + image[1][0].rgbtGreen + image[1][1].rgbtGreen;
    tmp_im[0][0].rgbtGreen = round(temp / 4.0);

    temp = image[0][0].rgbtBlue + image[0][1].rgbtBlue + image[1][0].rgbtBlue + image[1][1].rgbtBlue;
    tmp_im[0][0].rgbtBlue = round(temp / 4.0);

    // Middle pixels
    for (int j = 1; j < width - 1; j++)
    {
        temp = image[0][j - 1].rgbtRed + image[0][j].rgbtRed + image[0][j + 1].rgbtRed;
        temp = image[1][j - 1].rgbtRed + image[1][j].rgbtRed + image[1][j + 1].rgbtRed + temp;
        tmp_im[0][j].rgbtRed = round(temp / 6.0);

        temp = image[0][j - 1].rgbtGreen + image[0][j].rgbtGreen + image[0][j + 1].rgbtGreen;
        temp = image[1][j - 1].rgbtGreen + image[1][j].rgbtGreen + image[1][j + 1].rgbtGreen + temp;
        tmp_im[0][j].rgbtGreen = round(temp / 6.0);

        temp = image[0][j - 1].rgbtBlue + image[0][j].rgbtBlue + image[0][j + 1].rgbtBlue;
        temp = image[1][j - 1].rgbtBlue + image[1][j].rgbtBlue + image[1][j + 1].rgbtBlue + temp;
        tmp_im[0][j].rgbtBlue = round(temp / 6.0);
    }

    // Last pixel
    temp = image[0][width - 2].rgbtRed + image[0][width - 1].rgbtRed;
    temp = image[1][width - 2].rgbtRed + image[1][width - 1].rgbtRed + temp;
    tmp_im[0][width - 1].rgbtRed = round(temp / 4.0);

    temp = image[0][width - 2].rgbtGreen + image[0][width - 1].rgbtGreen;
    temp = image[1][width - 2].rgbtGreen + image[1][width - 1].rgbtGreen + temp;
    tmp_im[0][width - 1].rgbtGreen = round(temp / 4.0);

    temp = image[0][width - 2].rgbtBlue + image[0][width - 1].rgbtBlue;
    temp = image[1][width - 2].rgbtBlue + image[1][width - 1].rgbtBlue + temp;
    tmp_im[0][width - 1].rgbtBlue = round(temp / 4.0);

    // Middle rows
    // Cycle through rows
    for (int i = 1; i < height - 1; i++)
    {
        // First pixel
        temp = image[i - 1][0].rgbtRed + image[i - 1][1].rgbtRed;
        temp = image[i][0].rgbtRed + image[i][1].rgbtRed + temp;
        temp = image[i + 1][0].rgbtRed + image[i + 1][1].rgbtRed + temp;
        tmp_im[i][0].rgbtRed = round(temp / 6.0);

        temp = image[i - 1][0].rgbtGreen + image[i - 1][1].rgbtGreen;
        temp = image[i][0].rgbtGreen + image[i][1].rgbtGreen + temp;
        temp = image[i + 1][0].rgbtGreen + image[i + 1][1].rgbtGreen + temp;
        tmp_im[i][0].rgbtGreen = round(temp / 6.0);

        temp = image[i - 1][0].rgbtBlue + image[i - 1][1].rgbtBlue;
        temp = image[i][0].rgbtBlue + image[i][1].rgbtBlue + temp;
        temp = image[i + 1][0].rgbtBlue + image[i + 1][1].rgbtBlue + temp;
        tmp_im[i][0].rgbtBlue = round(temp / 6.0);

        // Middle pixels
        for (int j = 1; j < width; j++)
        {
            temp = image[i - 1][j - 1].rgbtRed + image[i - 1][j].rgbtRed + image[i - 1][j + 1].rgbtRed;
            temp = image[i][j - 1].rgbtRed + image[i][j].rgbtRed + image[i][j + 1].rgbtRed + temp;
            temp = image[i + 1][j - 1].rgbtRed + image[i + 1][j].rgbtRed + image[i + 1][j + 1].rgbtRed + temp;
            tmp_im[i][j].rgbtRed = round(temp / 9.0);


            temp = image[i - 1][j - 1].rgbtGreen + image[i - 1][j].rgbtGreen + image[i - 1][j + 1].rgbtGreen;
            temp = image[i][j - 1].rgbtGreen + image[i][j].rgbtGreen + image[i][j + 1].rgbtGreen + temp;
            temp = image[i + 1][j - 1].rgbtGreen + image[i + 1][j].rgbtGreen + image[i + 1][j + 1].rgbtGreen + temp;
            tmp_im[i][j].rgbtGreen = round(temp / 9.0);

            temp = image[i - 1][j - 1].rgbtBlue + image[i - 1][j].rgbtBlue + image[i - 1][j + 1].rgbtBlue;
            temp = image[i][j - 1].rgbtBlue + image[i][j].rgbtBlue + image[i][j + 1].rgbtBlue + temp;
            temp = image[i + 1][j - 1].rgbtBlue + image[i + 1][j].rgbtBlue + image[i + 1][j + 1].rgbtBlue + temp;
            tmp_im[i][j].rgbtBlue = round(temp / 9.0);
        }

        // Last pixel
        temp = image[i - 1][width - 2].rgbtRed + image[i - 1][width - 1].rgbtRed;
        temp = image[i][width - 2].rgbtRed + image[i][width - 1].rgbtRed + temp;
        temp = image[i + 1][width - 2].rgbtRed + image[i + 1][width - 1].rgbtRed + temp;
        tmp_im[i][width - 1].rgbtRed = round(temp / 6.0);

        temp = image[i - 1][width - 2].rgbtGreen + image[i - 1][width - 1].rgbtGreen;
        temp = image[i][width - 2].rgbtGreen + image[i][width - 1].rgbtGreen + temp;
        temp = image[i + 1][width - 2].rgbtGreen + image[i + 1][width - 1].rgbtGreen + temp;
        tmp_im[i][width - 1].rgbtGreen = round(temp / 6.0);

        temp = image[i - 1][width - 2].rgbtBlue + image[i - 1][width - 1].rgbtBlue;
        temp = image[i][width - 2].rgbtBlue + image[i][width - 1].rgbtBlue + temp;
        temp = image[i + 1][width - 2].rgbtBlue + image[i + 1][width - 1].rgbtBlue + temp;
        tmp_im[i][width - 1].rgbtBlue = round(temp / 6.0);
    }

    // Last row
    // First pixel
    temp = image[height - 2][0].rgbtRed + image[height - 2][1].rgbtRed;
    temp = image[height - 1][0].rgbtRed + image[height - 1][1].rgbtRed + temp;
    tmp_im[height - 1][0].rgbtRed = round(temp / 4.0);

    temp = image[height - 2][0].rgbtGreen + image[height - 2][1].rgbtGreen;
    temp = image[height - 1][0].rgbtGreen + image[height - 1][1].rgbtGreen + temp;
    tmp_im[height - 1][0].rgbtGreen = round(temp / 4.0);

    temp = image[height - 2][0].rgbtBlue + image[height - 2][1].rgbtBlue;
    temp = image[height - 1][0].rgbtBlue + image[height - 1][1].rgbtBlue + temp;
    tmp_im[height - 1][0].rgbtBlue = round(temp / 4.0);

    // Middle pixels
    for (int j = 1; j < width - 1; j++)
    {
        temp = image[height - 2][j - 1].rgbtRed + image[height - 2][j].rgbtRed + image[height - 2][j + 1].rgbtRed;
        temp = image[height - 1][j - 1].rgbtRed + image[height - 1][j].rgbtRed + image[height - 1][j + 1].rgbtRed + temp;
        tmp_im[height - 1][j].rgbtRed = round(temp / 6.0);

        temp = image[height - 2][j - 1].rgbtGreen + image[height - 2][j].rgbtGreen + image[height - 2][j + 1].rgbtGreen;
        temp = image[height - 1][j - 1].rgbtGreen + image[height - 1][j].rgbtGreen + image[height - 1][j + 1].rgbtGreen + temp;
        tmp_im[height - 1][j].rgbtGreen = round(temp / 6.0);

        temp = image[height - 2][j - 1].rgbtBlue + image[height - 2][j].rgbtBlue + image[height - 2][j + 1].rgbtBlue;
        temp = image[height - 1][j - 1].rgbtBlue + image[height - 1][j].rgbtBlue + image[height - 1][j + 1].rgbtBlue + temp;
        tmp_im[height - 1][j].rgbtBlue = round(temp / 6.0);
    }

    // Last pixel
    temp = image[height - 2][width - 2].rgbtRed + image[height - 2][width - 1].rgbtRed;
    temp = image[height - 1][width - 2].rgbtRed + image[height - 1][width - 1].rgbtRed + temp;
    tmp_im[height - 1][width - 1].rgbtRed = round(temp / 4.0);

    temp = image[height - 2][width - 2].rgbtGreen + image[height - 2][width - 1].rgbtGreen;
    temp = image[height - 1][width - 2].rgbtGreen + image[height - 1][width - 1].rgbtGreen + temp;
    tmp_im[height - 1][width - 1].rgbtGreen = round(temp / 4.0);

    temp = image[height - 2][width - 2].rgbtBlue + image[height - 2][width - 1].rgbtBlue;
    temp = image[height - 1][width - 2].rgbtBlue + image[height - 1][width - 1].rgbtBlue + temp;
    tmp_im[height - 1][width - 1].rgbtBlue = round(temp / 4.0);

    // Get data from temporary image to normal image
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j] = tmp_im[i][j];
        }
    }

    free(tmp_im);
    return;
}
