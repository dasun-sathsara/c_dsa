#include <stdio.h>

#include "counting_sort.h"

int counting_sort(int *array, size_t arrLength, int *ordering, size_t orderingLength)
{

    // Exit if the array is NULL
    if (array == NULL)
    {
        return -1;
    }

    // If the array is empty or has only one element, it is already sorted
    if (arrLength <= 1)
    {
        return 0;
    }

    // Create a frequency table
    int frequencyTable[orderingLength];

    for (size_t i = 0; i < orderingLength; i++)
    {
        frequencyTable[i] = 0;
    }

    for (size_t i = 0; i < arrLength; i++)
    {
        size_t idx = 0;
        char found = 0;
        for (; idx < orderingLength; idx++)
        {
            if (array[i] == ordering[idx])
            {
                found = 1;
                break;
            }
        }

        // Exit if the value is not in the ordering array
        if (!found)
        {
            fprintf(stderr, "Value %d couldn't be found in the ordering.\n", array[i]);
            return -1;
        }

        frequencyTable[idx] += 1;
    }

    // Prefix sum the frequency table
    for (size_t i = 1; i < orderingLength; i++)
    {
        frequencyTable[i] += frequencyTable[i - 1];
    }

    // Create a new array to store the sorted array
    int sorted_array[arrLength];

    for (int i = arrLength - 1; i >= 0; i--)
    {
        size_t idx = 0;
        for (; idx < orderingLength; idx++)
        {
            if (array[i] == ordering[idx])
            {
                break;
            }
        }

        sorted_array[frequencyTable[idx] - 1] = array[i];
        frequencyTable[idx] -= 1;
    }

    for (size_t i = 0; i < arrLength; i++)
    {
        array[i] = sorted_array[i];
    }

    return 0;
}
