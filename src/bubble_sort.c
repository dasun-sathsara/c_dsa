#include <stdio.h>

#include "bubble_sort.h"

int bubble_sort(int *arr, size_t length)
{
    int swapped;
    for (size_t i = 0; i < length - 1; i++)
    {
        swapped = 0;
        for (size_t j = 0; j < length - i - 1; j++)
        {
            if (arr[j + 1] < arr[j])
            {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
                swapped = 1;
            }
        }

        // If no two elements were swapped by inner loop, then the array is sorted.
        if (!swapped)
        {
            break;
        }
    }
    return 0;
}
