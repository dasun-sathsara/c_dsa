#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

typedef void *NodeData;
typedef struct _DoublyLinkedList DoublyLinkedList;
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

// Represents a null Node
#define NULL_NODE ((Node *)0)

/*
@brief Structure of a node in a doubly linked list
*/
struct _Node
{
    NodeData data;
    struct _Node *prev;
    struct _Node *next;
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
 * Searches for a node with the specified data in the given doubly linked list.
 *
 * @param list The doubly linked list to search in.
 * @param data The data to search for.
 * @param equal_func The function used to compare the data.
 * @return true if a node with the specified data is found, false otherwise.
 */
bool doubly_linked_list_search(DoublyLinkedList *list, NodeData data, EqualFunction equal_func);

/*
@brief Removes the first occurrence of the specified data from the doubly linked list.

@param list The doubly linked list to remove from.
@param data The data to remove.
@param equal_func The function used to compare the data.
@param free_data A boolean to free the data of the nodes.
@return true if the data was removed, false otherwise.
*/
bool doubly_linked_list_remove(DoublyLinkedList *list, NodeData data, EqualFunction equal_func, bool free_data);
