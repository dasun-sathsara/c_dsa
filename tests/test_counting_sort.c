#include "../src/counting_sort.h"
#include <criterion/criterion.h>
#include <stdio.h>

Test(counting_sort, test_counting_sort, .description = "Test counting sort")
{
    int arr[] = {3, 2, 1, 5, 4, 5, 3, 4, 1, 2, 2, 2, 4, 1, 2, 2, 4};
    int ordering[] = {3, 2, 1, 4, 5};
    int expected[] = {3, 3, 2, 2, 2, 2, 2, 2, 1, 1, 1, 4, 4, 4, 4, 5, 5};
    counting_sort(arr, sizeof(arr) / sizeof(arr[0]), ordering, sizeof(ordering) / sizeof(ordering[0]));
    for (int i = 0; i < 5; i++)
    {
        cr_assert_eq(arr[i], expected[i]);
    }
}

Test(counting_sort, test_counting_sort_empty, .description = "Test counting sort with empty array")
{
    int arr[] = {};
    int ordering[] = {3, 2, 1, 4, 5};
    int r = counting_sort(arr, 0, ordering, sizeof(ordering) / sizeof(ordering[0]));
    cr_assert_eq(r, 0);
}

Test(counting_sort, test_counting_sort_single, .description = "Test counting sort with single element")
{
    int arr[] = {1};
    int ordering[] = {3, 2, 1, 4, 5};
    int r = counting_sort(arr, 1, ordering, sizeof(ordering) / sizeof(ordering[0]));
    cr_assert_eq(r, 0);
}

Test(counting_sort, test_counting_sort_null, .description = "Test counting sort with null array")
{
    int *arr = NULL;
    int ordering[] = {3, 2, 1, 4, 5};
    int r = counting_sort(arr, 0, ordering, sizeof(ordering) / sizeof(ordering[0]));
    cr_assert_eq(r, -1);
}

Test(counting_sort, test_invalid_ordering_element, .description = "Test counting sort with invalid ordering element")
{
    int arr[] = {3, 2, 1, 5, 4, 5, 3, 4, 1, 2, 2, 2, 4, 1, 2, 2, 4};
    int ordering[] = {3, 2, 1, 4};
    int r = counting_sort(arr, sizeof(arr) / sizeof(arr[0]), ordering, sizeof(ordering) / sizeof(ordering[0]));
    cr_assert_eq(r, -1);
}
