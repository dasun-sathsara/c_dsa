#include <stdio.h>

#include "helpers.h"

void printIntegerArray(int *arr, size_t length)
{
    for (size_t i = 0; i < length; i++)
    {
        i != length - 1 ? printf("%d, ", *(arr + i)) : printf("%d\n", *(arr + i));
    }
}
