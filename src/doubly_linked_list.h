#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

typedef void *NodeData;
typedef struct _DoublyLinkedList DoublyLinkedList;
typedef struct _DoublyLinkedListIterator DoublyLinkedListIterator;
typedef struct _Node Node;

/*
@brief Struct of a doubly linked list
*/
struct _DoublyLinkedList
{
    struct _Node *head;
    struct _Node *tail;
    size_t size;
};

/*
@brief Structure of a node in a doubly linked list
*/
struct _Node
{
    NodeData data;
    struct _Node *prev;
    struct _Node *next;
};

/*
@brief Structure of a doubly linked list iterator
*/
struct _DoublyLinkedListIterator
{
    DoublyLinkedList *list;
    Node *current;
};

/**
 * @brief Function pointer type for comparing two NodeData.
 *
 * @param value1 The first NodeData to compare.
 * @param value2 The second NodeData to compare.
 * @return int Returns 0 if the items are equal, -1 if value1 < value2, 1 if value1 > value2.
 */
typedef int (*CompareFunction)(NodeData, NodeData);

/**
 * @brief Function pointer type for checking equality of two NodeData.
 *
 * @param value1 The first NodeData to compare.
 * @param value2 The second NodeData to compare.
 * @return bool Returns true if the items are equal, false otherwise.
 */
typedef bool (*EqualFunction)(NodeData, NodeData);

/**
 * @brief Creates a new doubly linked list.
 *
 * @return DoublyLinkedList* A pointer to the new doubly linked list.
 */
DoublyLinkedList *doubly_linked_list_new();

/**
 * @brief Frees the memory of the doubly linked list.
 *
 * @param list The doubly linked list to free.
 * @param free_data A boolean to free the data of the nodes.
 */
void doubly_linked_list_free(DoublyLinkedList **list, bool free_data);

/**
 * @brief Adds a new node to the beginning of the doubly linked list.
 *
 * @param list The doubly linked list to add to.
 * @param data The data to add to the list.
 * @return bool Returns true if the node was added, false otherwise.
 */
bool doubly_linked_list_prepend(DoublyLinkedList *list, NodeData data);

/**
 * @brief Adds a new node to the end of the doubly linked list.
 *
 * @param list The doubly linked list to add to.
 * @param data The data to add to the list.
 * @return bool Returns true if the node was added, false otherwise.
 */
bool doubly_linked_list_append(DoublyLinkedList *list, NodeData data);

/**
 * @brief Finds a node with the specified data in the given doubly linked list.
 *
 * @param list The doubly linked list to search in.
 * @param data The data to search for.
 * @param equal_func The function used to compare the data for equality.
 * @return A pointer to the found node, or NULL if the node is not found.
 */

Node *doubly_linked_list_find(DoublyLinkedList *list, NodeData data, EqualFunction equal_func);

/**
 * @brief Removes a node from the doubly linked list.
 *
 * @param list The doubly linked list from which to remove the node.
 * @param node The node to be removed from the list.
 * @param free_data A boolean value indicating whether to free the memory occupied by the removed node's data.
 * @return `true` if the node was successfully removed, `false` otherwise.
 */
bool doubly_linked_list_remove(DoublyLinkedList *list, Node *node, bool free_data);

/**
 * @brief Inserts a new node with the given data before the specified node in the doubly linked list.
 *
 * @param list The doubly linked list.
 * @param node The node before which the new node should be inserted.
 * @param data The data to be stored in the new node.
 * @return True if the insertion is successful, false otherwise.
 */
bool doubly_linked_list_insert_before(DoublyLinkedList *list, Node *node, NodeData data);

/**
 * @brief Inserts a new node with the given data after the specified node in the doubly linked list.
 *
 * @param list The doubly linked list.
 * @param node The node after which the new node should be inserted.
 * @param data The data to be stored in the new node.
 * @return True if the insertion is successful, false otherwise.
 */
bool doubly_linked_list_insert_after(DoublyLinkedList *list, Node *node, NodeData data);

/**
 * @brief Creates a new iterator for a doubly linked list and initializes it to the beginning of the list.
 *
 * @param list The doubly linked list to create an iterator for.
 * @return A pointer to the newly created iterator.
 */
DoublyLinkedListIterator *doubly_linked_list_iterator(DoublyLinkedList *list);

/**
 * @brief Frees the memory allocated for a doubly linked list iterator.
 *
 * @param iterator A pointer to the iterator to be freed.
 */
void doubly_linked_list_free_iterator(DoublyLinkedListIterator **iterator);

/**
 * @brief if there are more elements in the doubly linked list to iterate over.
 *
 * @param iterator The iterator to check.
 * @return true if there are more elements, false otherwise.
 */
bool doubly_linked_list_iterator_has_next(DoublyLinkedListIterator *iterator);

/**
 * @brief Moves the iterator to the next element in the doubly linked list.
 *
 * @param iterator The iterator to move.
 */
void doubly_linked_list_iterator_next(DoublyLinkedListIterator *iterator);

/**
 * @brief Retrieves the data of the current element in the doubly linked list.
 *
 * @param iterator The iterator to get the data from.
 * @return The data of the current element.
 */
NodeData doubly_linked_list_iterator_data(DoublyLinkedListIterator *iterator);
