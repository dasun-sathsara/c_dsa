#include "../src/arraylist.h"
#include <assert.h>
#include <criterion/criterion.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#define _GNU_SOURCE

Test(arraylist, test_arraylist_create, .description = "Test creating a new ArrayList")
{
    ArrayList *list = arraylist_new(10, NULL);
    cr_assert_not_null(list);
    cr_assert_eq(list->size, 0);
    cr_assert_eq(list->capacity, 10);
    arraylist_free(list);
}

Test(arraylist, test_arraylist_append, .description = "Test appending items to an ArrayList")
{
    ArrayList *list = arraylist_new(10, NULL);
    cr_assert_not_null(list);
    cr_assert_eq(list->size, 0);
    cr_assert_eq(list->capacity, 10);

    int a = 34;
    int b = 56;

    arraylist_append(list, &a);
    cr_assert_eq(list->size, 1);
    cr_assert_eq(list->capacity, 10);

    arraylist_append(list, &b);
    cr_assert_eq(list->size, 2);
    cr_assert_eq(list->capacity, 10);

    cr_assert_eq(*(int *)list->items[0], a);

    arraylist_free(list);
}

Test(arraylist, test_arraylist_remove, .description = "Test removing items from an ArrayList")
{
    ArrayList *list = arraylist_new(10, NULL);

    int a = 14;
    int b = 556;

    arraylist_append(list, &a);
    arraylist_append(list, &b);

    arraylist_remove(list, 0);
    cr_assert_eq(list->size, 1);
    cr_assert_eq(list->capacity, 10);
    cr_assert_eq(*(int *)list->items[0], b);

    arraylist_free(list);
}

void free_int(ArrayListItem data)
{
    free(data);
}

Test(arraylist, test_arraylist_remove_heap, .description = "Test removing heap allocated items from an ArrayList")
{
    ArrayList *list = arraylist_new(10, free_int);

    for (int i = 0; i < 10; i++)
    {
        int *a = malloc(sizeof(int));
        *a = i;
        arraylist_append(list, a);
    }

    // Assert that first item is 0
    cr_assert_eq(*(int *)list->items[0], 0);

    // Assert that last item is 9
    cr_assert_eq(*(int *)list->items[9], 9);

    // Remove a range of items
    arraylist_remove_range(list, 0, 5);

    // Assert that first item is 5
    cr_assert_eq(*(int *)list->items[0], 5);

    // Remove last item
    arraylist_remove(list, list->size - 1);

    // Assert that last item is 8
    cr_assert_eq(*(int *)list->items[list->size - 1], 8);

    arraylist_free(list);
}

bool int_equal(ArrayListItem item1, ArrayListItem item2)
{
    int a = *(int *)item1;
    int b = *(int *)item2;

    return a == b ? true : false;
}

Test(arraylist, test_arraylist_index_of, .description = "Test finding the index of an item in an ArrayList")
{
    ArrayList *list = arraylist_new(10, NULL);

    int a = 654;
    int b = 536;

    arraylist_append(list, &a);
    arraylist_append(list, &b);

    cr_assert_eq(arraylist_index_of(list, int_equal, &a), 0);
    cr_assert_eq(arraylist_index_of(list, int_equal, &b), 1);

    arraylist_free(list);
}

int int_compare(ArrayListItem item1, ArrayListItem item2)
{
    int a = *(int *)item1;
    int b = *(int *)item2;

    return a - b;
}

Test(arraylist, test_arraylist_sort, .description = "Test sorting an ArrayList")
{
    ArrayList *list = arraylist_new(10, NULL);

    int c = 1;
    int a = 2;
    int d = 3;
    int b = 4;
    int i = 5;
    int h = 6;
    int f = 7;
    int e = 8;
    int g = 9;

    arraylist_append(list, &a);
    arraylist_append(list, &b);
    arraylist_append(list, &c);
    arraylist_append(list, &d);
    arraylist_append(list, &e);
    arraylist_append(list, &f);
    arraylist_append(list, &g);
    arraylist_append(list, &h);
    arraylist_append(list, &i);

    arraylist_sort(list, int_compare);

    cr_assert_eq(*(int *)list->items[0], c);
    cr_assert_eq(*(int *)list->items[1], a);
    cr_assert_eq(*(int *)list->items[2], d);
    cr_assert_eq(*(int *)list->items[3], b);
    cr_assert_eq(*(int *)list->items[4], i);
    cr_assert_eq(*(int *)list->items[5], h);
    cr_assert_eq(*(int *)list->items[6], f);
    cr_assert_eq(*(int *)list->items[7], e);
    cr_assert_eq(*(int *)list->items[8], g);

    arraylist_free(list);
}

// Test the ArrayList for storing pointers to structures
typedef struct
{
    int id;
    char *name;
} TestStruct;

void free_test_struct(ArrayListItem data)
{
    TestStruct *test_struct = (TestStruct *)data;
    free(test_struct->name);
    free(test_struct);
}

Test(arraylist, test_arraylist_struct, .description = "Test using the ArrayList to store pointers to structures")
{
    ArrayList *list = arraylist_new(10, NULL);

    TestStruct *a = malloc(sizeof(TestStruct));
    a->id = 1;

    a->name = malloc(8);
    strcpy(a->name, "Test A");

    TestStruct *b = malloc(sizeof(TestStruct));
    b->id = 2;

    b->name = malloc(8);
    strcpy(b->name, "Test B");

    arraylist_append(list, a);
    arraylist_append(list, b);

    cr_assert_eq(((TestStruct *)list->items[0])->id, 1);
    cr_assert_str_eq(((TestStruct *)list->items[0])->name, "Test A");

    cr_assert_eq(((TestStruct *)list->items[1])->id, 2);
    cr_assert_str_eq(((TestStruct *)list->items[1])->name, "Test B");

    arraylist_free(list);
}
