#include "helpers.h"

#include <math.h>
#include <stdlib.h>
#include <stdio.h>

void calculate(int height, int width, RGBTRIPLE image[height][width], RGBTRIPLE temp_im[height + 2][width + 2]);

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

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{

    // Temporary image array
    RGBTRIPLE(*tmp_im)[width + 2] = calloc((height + 2), (width + 2) * sizeof(RGBTRIPLE));
    if (tmp_im == NULL)
    {
        printf("Not enough memory to store image for blurring.\n");
        return;
    }

    // Populate temporary array with additional row/column of zeroes on all sides
    // Easier to calculate that way, using one formula for all pixels of original image
    // First row
    for (int j = 0; j < width + 2; j++)
    {
        tmp_im[0][j].rgbtRed = 0;
        tmp_im[0][j].rgbtGreen = 0;
        tmp_im[0][j].rgbtBlue = 0;
    }

    // Middle rows
    for (int i = 1; i < height + 1; i++)
    {
        for (int j = 0; j < width + 2; j++)
        {
            if (j == 0 || j == width + 1)
            {
                tmp_im[i][j].rgbtRed = 0;
                tmp_im[i][j].rgbtGreen = 0;
                tmp_im[i][j].rgbtBlue = 0;
            }
            else
            {
                tmp_im[i][j].rgbtRed = image[i - 1][j - 1].rgbtRed;
                tmp_im[i][j].rgbtGreen = image[i - 1][j - 1].rgbtGreen;
                tmp_im[i][j].rgbtBlue = image[i - 1][j - 1].rgbtBlue;
            }
        }
    }

    // Last row
    for (int j = 0; j < width + 2; j++)
    {
        tmp_im[height + 1][j].rgbtRed = 0;
        tmp_im[height + 1][j].rgbtGreen = 0;
        tmp_im[height + 1][j].rgbtBlue = 0;
    }

    calculate(height, width, image, tmp_im);

    free(tmp_im);
    return;
}

void calculate(int height, int width, RGBTRIPLE image[height][width], RGBTRIPLE temp_im[height + 2][width + 2])
{
    // Temporary values;
    int Gx = 0, Gy = 0, temp = 0;

    for (int i = 1; i < height + 1; i++)
    {
        for (int j = 1; j < width + 1; j++)
        {
            // Red
            Gx = temp_im[i - 1][j - 1].rgbtRed * (-1) + temp_im[i - 1][j].rgbtRed * 0 + temp_im[i - 1][j + 1].rgbtRed * 1;
            Gx = temp_im[i][j - 1].rgbtRed * (-2) + temp_im[i][j].rgbtRed * 0 + temp_im[i][j + 1].rgbtRed * 2 + Gx;
            Gx = temp_im[i + 1][j - 1].rgbtRed * (-1) + temp_im[i + 1][j].rgbtRed * 0 + temp_im[i + 1][j + 1].rgbtRed * 1 + Gx;

            Gy = temp_im[i - 1][j - 1].rgbtRed * (-1) + temp_im[i - 1][j].rgbtRed * (-2) + temp_im[i - 1][j + 1].rgbtRed * (-1);
            Gy = temp_im[i][j - 1].rgbtRed * (0) + temp_im[i][j].rgbtRed * 0 + temp_im[i][j + 1].rgbtRed * 0 + Gy;
            Gy = temp_im[i + 1][j - 1].rgbtRed * (1) + temp_im[i + 1][j].rgbtRed * 2 + temp_im[i + 1][j + 1].rgbtRed * 1 + Gy;

            temp = round(sqrt(pow(Gx, 2) + pow(Gy, 2)) / 1.0);
            if (temp > 255)
            {
                image[i - 1][j - 1].rgbtRed = 255;
            }
            else
            {
                image[i - 1][j - 1].rgbtRed = temp;
            }

            // Green
            Gx = temp_im[i - 1][j - 1].rgbtGreen * (-1) + temp_im[i - 1][j].rgbtGreen * 0 + temp_im[i - 1][j + 1].rgbtGreen * 1;
            Gx = temp_im[i][j - 1].rgbtGreen * (-2) + temp_im[i][j].rgbtGreen * 0 + temp_im[i][j + 1].rgbtGreen * 2 + Gx;
            Gx = temp_im[i + 1][j - 1].rgbtGreen * (-1) + temp_im[i + 1][j].rgbtGreen * 0 + temp_im[i + 1][j + 1].rgbtGreen * 1 + Gx;

            Gy = temp_im[i - 1][j - 1].rgbtGreen * (-1) + temp_im[i - 1][j].rgbtGreen * (-2) + temp_im[i - 1][j + 1].rgbtGreen * (-1);
            Gy = temp_im[i][j - 1].rgbtGreen * (0) + temp_im[i][j].rgbtGreen * 0 + temp_im[i][j + 1].rgbtGreen * 0 + Gy;
            Gy = temp_im[i + 1][j - 1].rgbtGreen * (1) + temp_im[i + 1][j].rgbtGreen * 2 + temp_im[i + 1][j + 1].rgbtGreen * 1 + Gy;

            temp = round(sqrt(pow(Gx, 2) + pow(Gy, 2)) / 1.0);
            if (temp > 255)
            {
                image[i - 1][j - 1].rgbtGreen = 255;
            }
            else
            {
                image[i - 1][j - 1].rgbtGreen = temp;
            }

            // Blue
            Gx = temp_im[i - 1][j - 1].rgbtBlue * (-1) + temp_im[i - 1][j].rgbtBlue * 0 + temp_im[i - 1][j + 1].rgbtBlue * 1;
            Gx = temp_im[i][j - 1].rgbtBlue * (-2) + temp_im[i][j].rgbtBlue * 0 + temp_im[i][j + 1].rgbtBlue * 2 + Gx;
            Gx = temp_im[i + 1][j - 1].rgbtBlue * (-1) + temp_im[i + 1][j].rgbtBlue * 0 + temp_im[i + 1][j + 1].rgbtBlue * 1 + Gx;

            Gy = temp_im[i - 1][j - 1].rgbtBlue * (-1) + temp_im[i - 1][j].rgbtBlue * (-2) + temp_im[i - 1][j + 1].rgbtBlue * (-1);
            Gy = temp_im[i][j - 1].rgbtBlue * (0) + temp_im[i][j].rgbtBlue * 0 + temp_im[i][j + 1].rgbtBlue * 0 + Gy;
            Gy = temp_im[i + 1][j - 1].rgbtBlue * (1) + temp_im[i + 1][j].rgbtBlue * 2 + temp_im[i + 1][j + 1].rgbtBlue * 1 + Gy;

            temp = round(sqrt(pow(Gx, 2) + pow(Gy, 2)) / 1.0);
            if (temp > 255)
            {
                image[i - 1][j - 1].rgbtBlue = 255;
            }
            else
            {
                image[i - 1][j - 1].rgbtBlue = temp;
            }
        }
    }
}
