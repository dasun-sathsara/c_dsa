#include <stdio.h>

#include "selection_sort.h"

int selectionSort(int *arr, size_t length)
{
    for (size_t i = 0; i < length; i++)
    {
        size_t currentLowest = i;
        for (size_t j = i; j < length; j++)
        {
            if (arr[j] < arr[currentLowest])
            {
                currentLowest = j;
            }
        }

        // Only swap if the smallest element is not already in its correct position
        if (currentLowest != i)
        {
            int temp = arr[i];
            arr[i] = arr[currentLowest];
            arr[currentLowest] = temp;
        }
    }
    return 0;
}
