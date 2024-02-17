#include <stdio.h>

#include "quick_sort.h"

int quick_sort(int *array, size_t arrLength)
{
    int *start = array;

    if (start == NULL)
    {
        return -1;
    }

    // If the array is empty or has only one element, it is already sorted
    if (arrLength <= 1)
    {
        return 0;
    }

    int pivot;
    int temp;

    // Set the pivot to the last element in the array
    pivot = start[arrLength - 1];

    int i = -1;
    int j = 0;

    // Partition the array
    while (j < arrLength)
    {
        if (start[j] <= pivot)
        {
            temp = start[j];
            i++;
            start[j] = start[i];
            start[i] = temp;
        }
        j++;
    }

    size_t left_partition_length = i;
    size_t right_partition_length = arrLength - i - 1;

    // Recursively sort the two partitions
    quick_sort(start, left_partition_length);
    quick_sort(start + i + 1, right_partition_length);
    return 0;
}
