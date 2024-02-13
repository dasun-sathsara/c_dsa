#include <stdio.h>

/**
 * Sorts an array using the counting sort algorithm.
 *
 * @param array The array to be sorted.
 * @param arrLength The length of the array.
 * @param ordering The ordering array used to determine the order of elements.
 * @param orderingLength The length of the ordering array.
 */
int counting_sort(int *array, size_t arrLength, int *ordering, size_t orderingLength);
