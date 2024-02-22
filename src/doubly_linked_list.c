#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "doubly_linked_list.h"

DoublyLinkedList *doubly_linked_list_new(FreeNodeDataFunction free_func)
{
    DoublyLinkedList *new_ddl;

    new_ddl = malloc(sizeof(DoublyLinkedList));

    if (new_ddl == NULL)
    {
        perror("Failed to allocate memory for new DoublyLinkedList");
        return NULL;
    }

    new_ddl->size = 0;
    new_ddl->head = NULL;
    new_ddl->tail = NULL;
    new_ddl->free_func = free_func;

    return new_ddl;
}

void doubly_linked_list_free(DoublyLinkedList *list)
{
    if (list == NULL)
    {
        return;
    }

    Node *current = list->head;
    Node *next;

    while (current != NULL)
    {
        next = current->next;

        // If the free function is not NULL, use it to free the node's data
        if (list->free_func != NULL)
        {
            list->free_func(current->data);
        }

        free(current);
        current = next;
    }

    free(list);
}

bool doubly_linked_list_prepend(DoublyLinkedList *list, NodeData data)
{
    if (list == NULL)
    {
        perror("List is NULL");
        return false;
    }

    Node *new_node = malloc(sizeof(Node));

    if (new_node == NULL)
    {
        perror("Failed to allocate memory for new Node");
        return false;
    }
    new_node->data = data;
    new_node->prev = NULL;

    // If the list is not empty
    if (list->head != NULL)
    {
        list->head->prev = new_node;
        new_node->next = list->head;
        list->head = new_node;
    }
    // If the list is empty
    else
    {
        list->head = new_node;
        new_node->next = NULL;
        list->tail = new_node;
    }

    list->size += 1;

    return true;
}

bool doubly_linked_list_append(DoublyLinkedList *list, NodeData data)
{
    if (list == NULL)
    {
        perror("List is NULL");
        return false;
    }

    Node *new_node = malloc(sizeof(Node));

    if (new_node == NULL)
    {
        perror("Failed to allocate memory for new Node");
        return false;
    }
    new_node->data = data;
    new_node->next = NULL;

    // If the list is not empty
    if (list->tail != NULL)
    {
        list->tail->next = new_node;
        new_node->prev = list->tail;
        list->tail = new_node;
    }
    // If the list is empty
    else
    {
        list->head = new_node;
        list->tail = new_node;
        new_node->prev = NULL;
    }

    list->size += 1;

    return true;
}

Node *doubly_linked_list_find(DoublyLinkedList *list, NodeData data, EqualFunction equal_func)
{
    if (list == NULL)
    {
        perror("List is NULL");
        return NULL;
    }

    Node *current = list->head;

    while (current != NULL)
    {
        if (equal_func(current->data, data))
        {
            return current;
        }
        current = current->next;
    }

    return NULL;
}

bool doubly_linked_list_remove(DoublyLinkedList *list, Node *node)
{
    if (list == NULL)
    {
        perror("List is NULL");
        return false;
    }

    // Only one node in the list
    if (list->size == 1)
    {
        list->head = NULL;
        list->tail = NULL;
    }
    // Node is the head
    else if (list->head == node)
    {
        list->head = node->next;
        node->next->prev = NULL;
    }
    // Node is the tail
    else if (list->tail == node)
    {
        list->tail = node->prev;
        node->prev->next = NULL;
    }
    // Node is in the middle
    else
    {
        node->prev->next = node->next;
        node->next->prev = node->prev;
    }

    // If the free function is not NULL, use it to free the node's data
    if (list->free_func != NULL)
    {
        list->free_func(node->data);
    }

    free(node);
    list->size -= 1;

    return true;
}

bool doubly_linked_list_insert_before(DoublyLinkedList *list, Node *node, NodeData data)
{
    if (list == NULL)
    {
        perror("List is NULL");
        return false;
    }

    if (node == NULL)
    {
        perror("Node is NULL");
        return false;
    }

    Node *new_node = malloc(sizeof(Node));

    if (new_node == NULL)
    {
        perror("Failed to allocate memory for new Node");
        return false;
    }
    new_node->data = data;

    // If the node is the head
    if (list->head == node)
    {
        list->head = new_node;
        new_node->prev = NULL;
        new_node->next = node;
    }
    // If the node is not the head
    else
    {
        new_node->next = node;
        new_node->prev = node->prev;
        node->prev->next = new_node;
    }
    node->prev = new_node;
    list->size += 1;

    return true;
}

bool doubly_linked_list_insert_after(DoublyLinkedList *list, Node *node, NodeData data)
{
    if (list == NULL)
    {
        perror("List is NULL");
        return false;
    }

    if (node == NULL)
    {
        perror("Node is NULL");
        return false;
    }

    Node *new_node = malloc(sizeof(Node));

    if (new_node == NULL)
    {
        perror("Failed to allocate memory for new Node");
        return false;
    }
    new_node->data = data;

    // If the node is the tail
    if (list->tail == node)
    {
        list->tail = new_node;
        new_node->next = NULL;
        new_node->prev = node;
    }
    // If the node is not the tail
    else
    {
        new_node->prev = node;
        new_node->next = node->next;
        node->next->prev = new_node;
    }
    node->next = new_node;
    list->size += 1;

    return true;
}

DoublyLinkedListIterator *doubly_linked_list_iterator(DoublyLinkedList *list)
{
    DoublyLinkedListIterator *iterator;

    iterator = malloc(sizeof(DoublyLinkedListIterator));

    if (iterator == NULL)
    {
        perror("Failed to allocate memory for new DoublyLinkedListIterator");
        return iterator;
    }

    iterator->list = list;
    iterator->current = list->head;

    return iterator;
}

void doubly_linked_list_free_iterator(DoublyLinkedListIterator *iterator)
{
    free(iterator);
}

bool doubly_linked_list_iterator_has_next(DoublyLinkedListIterator *iterator)
{
    return iterator->current != NULL;
}

void doubly_linked_list_iterator_next(DoublyLinkedListIterator *iterator)
{
    if (iterator->current != NULL)
    {
        iterator->current = iterator->current->next;
    }
}

NodeData doubly_linked_list_iterator_data(DoublyLinkedListIterator *iterator)
{
    if (iterator->current != NULL)
    {
        return iterator->current->data;
    }
    return NULL; // or some other default value
}
