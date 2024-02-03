#include "../src/arraylist.h"
#include <assert.h>
#include <stdio.h>

void try_out()
{
    ArrayList *arr;
    arr = arraylist_new(10);
    printf("The capacity of the list is: %zu\n", arr->capacity);

    // Add elements to the list
    int a = 10;
    int b = 22;

    arraylist_append(arr, &a);
    arraylist_append(arr, &b);

    for (int i = 0; i < 10; i++)
    {
        int *t = malloc(sizeof(int));
        *t = i;
        arraylist_append(arr, t);
    }

    for (size_t i = 0; i < arr->size; i++)
    {
        printf("The element at index %zu is: %d\n", i, *(int *)arr->items[i]);
    }

    // Free dynamically allocated memory
    for (size_t i = 2; i < arr->size; i++)
    {
        free(arr->items[i]);
    }

    arraylist_free(arr);
}

int main()
{
    printf("Testing ArrayList\n");
    try_out();
    ArrayList *list = arraylist_new(10);
    assert(list != NULL);
    assert(list->size == 0);
    assert(list->capacity == 11);
    assert(list->items != NULL);

    return 0;
}
