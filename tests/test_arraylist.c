#include "../src/arraylist.h"
#include <assert.h>
#include <criterion/criterion.h>
#include <stdbool.h>
#include <stdio.h>

Test(arraylist, test_arraylist_create, .description = "Test creating a new ArrayList")
{
    ArrayList *list = arraylist_new(10);
    cr_assert_not_null(list);
    cr_assert_eq(list->size, 0);
    cr_assert_eq(list->capacity, 10);
    arraylist_free(list);
}

Test(arraylist, test_arraylist_append, .description = "Test appending items to an ArrayList")
{
    ArrayList *list = arraylist_new(10);
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
    ArrayList *list = arraylist_new(10);

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

bool cb(ArrayListItem item1, ArrayListItem item2)
{
    int a = *(int *)item1;
    int b = *(int *)item2;

    return a == b ? true : false;
}

Test(arraylist, test_arraylist_index_of, .description = "Test finding the index of an item in an ArrayList")
{
    ArrayList *list = arraylist_new(10);

    int a = 654;
    int b = 536;

    arraylist_append(list, &a);
    arraylist_append(list, &b);

    cr_assert_eq(arraylist_index_of(list, cb, &a), 0);
    cr_assert_eq(arraylist_index_of(list, cb, &b), 1);

    arraylist_free(list);
}
