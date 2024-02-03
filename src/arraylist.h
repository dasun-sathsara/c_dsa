#include <stdbool.h>
#include <stdlib.h>
#include <sys/types.h>

typedef void *ArrayListItem;

typedef struct _ArrayList ArrayList;

/**
 * @brief Function pointer type for comparing two ArrayListItems.
 *
 * @param value1 The first ArrayListItem to compare.
 * @param value2 The second ArrayListItem to compare.
 * @return int Returns 0 if the items are equal, -1 if value1 < value2, 1 if value1 > value2.
 */
typedef int (*ArrayListCompareFunc)(ArrayListItem value1, ArrayListItem value2);

/**
 * @brief Function pointer type for checking equality of two ArrayListItems.
 *
 * @param value1 The first ArrayListItem to compare.
 * @param value2 The second ArrayListItem to compare.
 * @return bool Returns true if the items are equal, false otherwise.
 */
typedef bool (*ArrayListEqualFunc)(ArrayListItem value1, ArrayListItem value2);

/**
 * @brief Structure representing an ArrayList.
 */
struct _ArrayList
{
    ArrayListItem *items; // Array of items
    size_t size;          // Number of items in the list
    size_t capacity;      // Maximum number of items the list can hold
};

/**
 * @brief Creates a new ArrayList with the specified capacity.
 *
 * @param capacity The initial capacity of the ArrayList.
 * @return ArrayList* Returns a pointer to the newly created ArrayList.
 */
ArrayList *arraylist_new(size_t capacity);

/**
 * @brief Frees the memory occupied by the ArrayList.
 *
 * @param list The ArrayList to be freed.
 */
void arraylist_free(ArrayList *list);

/**
 * @brief Resizes the ArrayList to double its current capacity.
 *
 * @param arraylist The ArrayList to be resized.
 * @return bool Returns true if the resize operation is successful, false otherwise.
 */
static bool arraylist_resize(ArrayList *arraylist);

/**
 * @brief Inserts an item at the specified index in the ArrayList.
 *
 * @param list The ArrayList in which to insert the item.
 * @param index The index at which to insert the item.
 * @param data The item to be inserted.
 * @return bool Returns true if the item is successfully inserted, false otherwise.
 */
bool arraylist_insert(ArrayList *list, size_t index, ArrayListItem data);

/**
 * @brief Prepends an item to the beginning of the ArrayList.
 *
 * @param list The ArrayList to which the item should be prepended.
 * @param data The item to be prepended.
 * @return bool Returns true if the item is successfully prepended, false otherwise.
 */
bool arraylist_prepend(ArrayList *list, ArrayListItem data);

/**
 * @brief Appends an item to the end of the ArrayList.
 *
 * @param list The ArrayList to which the item should be appended.
 * @param data The item to be appended.
 * @return bool Returns true if the item is successfully appended, false otherwise.
 */
bool arraylist_append(ArrayList *list, ArrayListItem data);

/**
 * @brief Removes a range of items from the ArrayList.
 *
 * @param list The ArrayList from which to remove the items.
 * @param start The starting index of the range to be removed.
 * @param end The ending index of the range to be removed.
 * @return bool Returns true if the items are successfully removed, false otherwise.
 */
bool arraylist_remove_range(ArrayList *list, size_t start, size_t end);

/**
 * @brief Removes an item at the specified index from the ArrayList.
 *
 * @param list The ArrayList from which to remove the item.
 * @param index The index of the item to be removed.
 * @return bool Returns true if the item is successfully removed, false otherwise.
 */
bool arraylist_remove(ArrayList *list, size_t index);

/**
 * @brief Returns the index of the first occurrence of the specified item in the ArrayList.
 *
 * This function searches for the specified item in the given ArrayList and returns the index of the first occurrence.
 * The search is performed using the provided callback function `cb` to compare the items in the ArrayList.
 *
 * @param list The ArrayList in which to search for the item.
 * @param cb The callback function used to compare the items in the ArrayList.
 * @param data The item to search for.
 * @return ssize_t Returns the index of the item if found, or -1 if not found.
 */
ssize_t arraylist_index_of(ArrayList *list, ArrayListEqualFunc cb, ArrayListItem data);

/**
 * @brief Clears all items from the ArrayList.
 *
 * @param list The ArrayList to be cleared.
 */
void arraylist_clear(ArrayList *list);

/**
 * @brief Sorts the items in the ArrayList using the specified compare function.
 *
 * @param list The ArrayList to be sorted.
 * @param compare_func The compare function used for sorting.
 */
void arraylist_sort(ArrayList *list, ArrayListCompareFunc compare_func);
