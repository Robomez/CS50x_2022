#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <stdlib.h>

void sort (int min, int max, int array[], int arrsize);
void merge(int min1, int max1, int min2, int max2, int array[], int arrsize);

int main (void)
{
    // Get string and convert it to array of ints.
    int len = 0;
    do
    {
        len = get_int("How many numbers? ");
    }
    while (len < 1);

    int arr[len];
    int arr_el = 0;

    for (int i = 0; i < len; i++)
    {
        do
        {
            arr_el= get_int("Number [%i] ", i + 1);
        }
        while (arr_el < 0);
        arr[i] = arr_el;
    }

    // We have an array arr[len]
    // Sort it
    sort (0, len - 1, arr, len);

    // Print sorted array
    printf("\nsorted\n");
    for (int i = 0; i < len; i++)
    {
        printf("%i ", arr[i]);
    }
        printf("\n");
}

void sort (int min, int max, int array[], int arrsize)
{
    // Basic case
    if (min >= max)
    {
        return;
    }
    // Sort left half
    int mid = (min + max) / 2;
    sort(min, mid, array, (mid - min));
    // Sort right half
    sort(mid + 1, max, array, (max - (mid + 1)));
    // Merge halves
    merge(min, mid, mid + 1, max, array, (max - min));
}

void merge(int min1, int max1, int min2, int max2, int array[], int arrsize)
{
    // i - 1st halfs 1st element, j - second halfs 1st el
    int i = min1, j = min2, count = 0;

    // We need a temporaty array
    int temp[arrsize];

    // While both halves are less then max
    while (i <= max1 && j <= max2)
    {
        // If ith arr element is smaller, put it in temp array, else put jth el. add 1 to count
        if (array[i] < array[j])
        {
            temp[count] = array[i];
            count++;
            i++;
        }
        else
        {
            temp[count] = array[j];
            count++;
            j++;
        }
    }

    // If one half has less elements, put other half in temp array. Only one of halves might be bigger
    while (i <= max1)
    {
        temp[count] = array[i];
        count++;
        i++;
    }
    while (j <= max2)
    {
        temp[count] = array[j];
        count++;
        j++;
    }

    // Put everything in an original array
    for (i = min1, j = 0; i <= max2; i++, j++)
    {
        array[i] = temp[j];
    }
}
