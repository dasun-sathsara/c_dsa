#include "../src/quick_sort.h"
#include <criterion/criterion.h>
#include <stdio.h>

Test(quick_sort, test_quick_sort, .description = "Test quick sort")
{
    int arr[] = {3, 2, 1, 5, 4};
    int expected[] = {1, 2, 3, 4, 5};
    quick_sort(arr, 5);
    for (int i = 0; i < 5; i++)
    {
        cr_assert_eq(arr[i], expected[i]);
    }
}

Test(quick_sort, test_quick_sort_empty, .description = "Test quick sort with empty array")
{
    int arr[] = {};
    int r = quick_sort(arr, 0);
    cr_assert_eq(r, 0);
}

Test(quick_sort, test_quick_sort_single, .description = "Test quick sort with single element")
{
    int arr[] = {1};
    int r = quick_sort(arr, 1);
    cr_assert_eq(r, 0);
}

Test(quick_sort, test_quick_sort_null, .description = "Test quick sort with null array")
{
    int *arr = NULL;
    int r = quick_sort(arr, 0);
    cr_assert_eq(r, -1);
}

Test(quick_sort, test_quick_sort_large, .description = "Test quick sort with large array")
{
    int arr[1000];
    for (int i = 0; i < 1000; i++)
    {
        arr[i] = 1000 - i;
    }
    quick_sort(arr, 1000);
    for (int i = 0; i < 1000; i++)
    {
        cr_assert_eq(arr[i], i + 1);
    }
}
