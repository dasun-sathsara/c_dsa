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

bool int_equal(ArrayListItem item1, ArrayListItem item2)
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
    ArrayList *list = arraylist_new(10);

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
