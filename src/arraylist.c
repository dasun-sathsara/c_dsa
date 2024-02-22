#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>

#include "arraylist.h"

#define DEFAULT_ARRAY_CAPACITY 16

ArrayList *arraylist_new(size_t capacity, ArrayListItemFreeFunc free_func)
{
    if (capacity == 0)
    {
        capacity = DEFAULT_ARRAY_CAPACITY;
    }

    ArrayList *new_arraylist = malloc(sizeof(ArrayList));

    if (new_arraylist == NULL)
    {
        perror("Failed to allocate memory for new ArrayList");
        return NULL;
    }

    new_arraylist->capacity = capacity;
    new_arraylist->size = 0;
    new_arraylist->items = malloc(capacity * sizeof(ArrayListItem));
    new_arraylist->free_func = free_func;

    if (new_arraylist->items == NULL)
    {
        perror("Failed to allocate memory for ArrayList items");
        free(new_arraylist);
        return NULL;
    }

    return new_arraylist;
}

void arraylist_free(ArrayList *arraylist)
{
    if (arraylist != NULL)
    {

        // If the free function is not NULL, free the items
        if (arraylist->free_func != NULL)
        {
            for (size_t i = 0; i < arraylist->size; i++)
            {
                arraylist->free_func(arraylist->items[i]);
            }
        }

        free(arraylist->items);
        free(arraylist);
    }
}

// Resize the arraylist to double its current capacity
static bool arraylist_resize(ArrayList *arraylist)
{
    size_t new_capacity = arraylist->capacity * 2;
    ArrayListItem *data = realloc(arraylist->items, sizeof(ArrayListItem) * new_capacity);

    if (data == NULL)
    {
        perror("Failed to allocate memory for resizing ArrayList");
        return false;
    }
    else
    {
        arraylist->items = data;
        arraylist->capacity = new_capacity;
        return true;
    }
}

bool arraylist_insert(ArrayList *list, size_t index, ArrayListItem data)
{
    // Check if index is out of bounds
    if (index > list->size)
    {
        perror("Index out of bounds in arraylist_insert");
        return false;
    }

    // Resize the arraylist if it is full
    if (list->size == list->capacity)
    {
        if (!arraylist_resize(list))
        {
            return false;
        }
    }

    memmove(&list->items[index + 1], &list->items[index], (list->size - index) * sizeof(ArrayListItem));
    list->items[index] = data;
    ++list->size;

    return true;
}

bool arraylist_append(ArrayList *list, ArrayListItem data)
{
    return arraylist_insert(list, list->size, data);
}

bool arraylist_prepend(ArrayList *list, ArrayListItem data)
{
    return arraylist_insert(list, 0, data);
}

bool arraylist_remove_range(ArrayList *list, size_t start, size_t end)
{

    // Check if start and end are out of bounds
    if (start >= end || end > list->size)
    {
        perror("Start or end index out of bounds in arraylist_remove_range");
        return false;
    }

    // Free the items if the free function is not NULL
    if (list->free_func != NULL)
    {
        for (size_t i = start; i < end; i++)
        {
            list->free_func(list->items[i]);
        }
    }

    // Move the items after the range to the start of the range
    memmove(&list->items[start], &list->items[end], (list->size - end) * sizeof(ArrayListItem));
    list->size -= (end - start);

    return true;
}

bool arraylist_remove(ArrayList *list, size_t index)
{
    return arraylist_remove_range(list, index, index + 1);
}

ssize_t arraylist_index_of(ArrayList *list, ArrayListEqualFunc cb, ArrayListItem data)
{

    // Check if the callback function is NULL
    if (cb == NULL)
    {
        perror("Callback function is NULL in arraylist_index_of");
        return -1;
    }

    for (size_t i = 0; i < list->size; i++)
    {
        if (cb(list->items[i], data))
        {
            return i;
        }
    }

    return -1;
}

static void quick_sort(ArrayListItem *start, size_t length, ArrayListCompareFunc compare_func)
{

    if (start == NULL || compare_func == NULL)
    {
        return;
    }

    // If the array is empty or has only one element, it is already sorted
    if (length <= 1)
    {
        return;
    }

    ArrayListItem pivot;
    ArrayListItem temp;

    // Set the pivot to the last element in the array
    pivot = start[length - 1];

    int i = -1;
    int j = 0;

    // Partition the array
    while (j < length)
    {
        if (compare_func(start[j], pivot) <= 0)
        {
            temp = start[j];
            i++;
            start[j] = start[i];
            start[i] = temp;
        }
        j++;
    }

    size_t left_partition_length = i;
    size_t right_partition_length = length - i - 1;

    // Recursively sort the two partitions
    quick_sort(start, left_partition_length, compare_func);
    quick_sort(start + i + 1, right_partition_length, compare_func);
}

void arraylist_sort(ArrayList *list, ArrayListCompareFunc compare_func)
{

    quick_sort(list->items, list->size, compare_func);
}

void arraylist_clear(ArrayList *list)
{
    // Set the size to 0, effectively clearing the arraylist
    list->size = 0;
}
