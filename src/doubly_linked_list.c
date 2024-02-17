#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "doubly_linked_list.h"

DoublyLinkedList *doubly_linked_list_new()
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

    return new_ddl;
}

void doubly_linked_list_free(DoublyLinkedList **list, bool free_data)
{
    if (*list == NULL)
    {
        return;
    }

    Node *current = (*list)->head;
    Node *next;

    while (current != NULL)
    {
        next = current->next;
        if (free_data)
        {
            free(current->data);
        }
        free(current);
        current = next;
    }

    free(*list);
    *list = NULL;
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

bool doubly_linked_list_remove(DoublyLinkedList *list, Node *node, bool free_data)
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

    if (free_data)
    {
        free(node->data);
    }
    free(node);
    list->size -= 1;

    return true;
}
