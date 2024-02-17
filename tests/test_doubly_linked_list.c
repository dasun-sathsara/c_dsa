#include <criterion/criterion.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../src/doubly_linked_list.h"

Test(doubly_linked_list_new, test_doubly_linked_list_new, .description = "Test creation of a new doubly linked list.")
{
    DoublyLinkedList *list = doubly_linked_list_new();
    cr_assert_not_null(list, "doubly_linked_list_new() failed");
    cr_assert_eq(list->size, 0, "doubly_linked_list_new() failed");
    cr_assert_null(list->head, "doubly_linked_list_new() failed");
    cr_assert_null(list->tail, "doubly_linked_list_new() failed");
    doubly_linked_list_free(&list, false);
}

Test(doubly_linked_list_free, test_doubly_linked_list_free, .description = "Test freeing of a doubly linked list.")
{
    DoublyLinkedList *list = doubly_linked_list_new();
    cr_assert_not_null(list, "doubly_linked_list_new() failed");
    doubly_linked_list_free(&list, false);
    cr_assert_null(list, "doubly_linked_list_free() failed");
}

Test(doubly_linked_list_append, test_doubly_linked_list_append,
     .description = "Test appending a node to a doubly linked list.")
{
    DoublyLinkedList *list = doubly_linked_list_new();
    cr_assert_not_null(list, "doubly_linked_list_new() failed");

    int *a = malloc(sizeof(int));
    *a = 1;

    int *b = malloc(sizeof(int));
    *b = 20;

    int *c = malloc(sizeof(int));
    *c = 300;

    doubly_linked_list_append(list, a);
    cr_assert_eq(list->size, 1, "doubly_linked_list_append() failed");
    cr_assert_not_null(list->head, "doubly_linked_list_append() failed");
    cr_assert_not_null(list->tail, "doubly_linked_list_append() failed");
    cr_assert_eq(list->head, list->tail, "doubly_linked_list_append() failed");
    cr_assert_eq(list->head->data, a, "doubly_linked_list_append() failed");
    cr_assert_null(list->head->prev, "doubly_linked_list_append() failed");
    cr_assert_null(list->head->next, "doubly_linked_list_append() failed");

    doubly_linked_list_append(list, b);
    cr_assert_eq(list->size, 2, "doubly_linked_list_append() failed");
    cr_assert_not_null(list->head, "doubly_linked_list_append() failed");
    cr_assert_not_null(list->tail, "doubly_linked_list_append() failed");
    cr_assert_not_null(list->head->next, "doubly_linked_list_append() failed");
    cr_assert_eq(list->head->next, list->tail, "doubly_linked_list_append() failed");
    cr_assert_eq(list->tail->data, b, "doubly_linked_list_append() failed");
    cr_assert_eq(list->tail->prev, list->head, "doubly_linked_list_append() failed");
    cr_assert_null(list->tail->next, "doubly_linked_list_append() failed");

    doubly_linked_list_append(list, c);

    doubly_linked_list_free(&list, true);
    cr_assert_null(list, "doubly_linked_list_free() failed");
}

Test(doubly_linked_list_prepend, test_doubly_linked_list_prepend,
     .description = "Test prepending a node to a doubly linked list.")
{
    DoublyLinkedList *list = doubly_linked_list_new();
    cr_assert_not_null(list, "doubly_linked_list_new() failed");

    int *a = malloc(sizeof(int));
    *a = 1;

    int *b = malloc(sizeof(int));
    *b = 20;

    int *c = malloc(sizeof(int));
    *c = 300;

    doubly_linked_list_prepend(list, a);
    cr_assert_eq(list->size, 1, "doubly_linked_list_prepend() failed");
    cr_assert_not_null(list->head, "doubly_linked_list_prepend() failed");
    cr_assert_not_null(list->tail, "doubly_linked_list_prepend() failed");
    cr_assert_eq(list->head, list->tail, "doubly_linked_list_prepend() failed");
    cr_assert_eq(list->head->data, a, "doubly_linked_list_prepend() failed");
    cr_assert_null(list->head->prev, "doubly_linked_list_prepend() failed");
    cr_assert_null(list->head->next, "doubly_linked_list_prepend() failed");

    doubly_linked_list_prepend(list, b);
    cr_assert_eq(list->size, 2, "doubly_linked_list_prepend() failed");
    cr_assert_not_null(list->head, "doubly_linked_list_prepend() failed");
    cr_assert_not_null(list->tail, "doubly_linked_list_prepend() failed");
    cr_assert_not_null(list->head->next, "doubly_linked_list_prepend() failed");
    cr_assert_eq(list->head, list->tail->prev, "doubly_linked_list_prepend() failed");
    cr_assert_eq(list->head->data, b, "doubly_linked_list_prepend() failed");
    cr_assert_null(list->head->prev, "doubly_linked_list_prepend() failed");
    cr_assert_eq(list->head->next, list->tail, "doubly_linked_list_prepend() failed");
    cr_assert_eq(list->tail->data, a, "doubly_linked_list_prepend() failed");
    cr_assert_eq(list->tail->prev, list->head, "doubly_linked_list_prepend() failed");
    cr_assert_null(list->tail->next, "doubly_linked_list_prepend() failed");

    doubly_linked_list_prepend(list, c);

    cr_assert_eq(list->head->next->next->data, a, "doubly_linked_list_prepend() failed");

    doubly_linked_list_free(&list, true);
    cr_assert_null(list, "doubly_linked_list_free() failed");
}

bool int_equal(NodeData item1, NodeData item2)
{
    int a = *(int *)item1;
    int b = *(int *)item2;

    return a == b ? true : false;
}

void print_dll_int(DoublyLinkedList *list)
{
    printf("------------------\n");
    DoublyLinkedListIterator *it = doubly_linked_list_iterator(list);
    while (doubly_linked_list_iterator_has_next(it))
    {
        NodeData data = doubly_linked_list_iterator_data(it);
        printf("%d\n", *(int *)data);
        doubly_linked_list_iterator_next(it);
    }

    doubly_linked_list_free_iterator(&it);
    printf("------------------\n");
}

Test(doubly_linked_list_find, test_doubly_linked_list_find,
     .description = "Test searching for a node in a doubly linked list.")
{
    DoublyLinkedList *list = doubly_linked_list_new();
    cr_assert_not_null(list, "doubly_linked_list_new() failed");

    for (int i = 0; i < 10; i++)
    {
        int *a = malloc(sizeof(int));
        *a = i;

        if (i % 2 == 0)
        {
            doubly_linked_list_prepend(list, a);
        }
        else
        {
            doubly_linked_list_append(list, a);
        }
    }

    int a = 9;
    Node *r = doubly_linked_list_find(list, &a, int_equal);
    cr_assert_not_null(r, "doubly_linked_list_find() failed");

    int b = 11;
    r = doubly_linked_list_find(list, &b, int_equal);
    cr_assert_null(r, "doubly_linked_list_find() failed");

    doubly_linked_list_free(&list, true);
}

Test(doubly_linked_list_remove, test_doubly_linked_list_remove,
     .description = "Test removing a node from a doubly linked list.")
{
    DoublyLinkedList *list = doubly_linked_list_new();
    cr_assert_not_null(list, "doubly_linked_list_new() failed");

    for (int i = 0; i < 10; i++)
    {
        int *a = malloc(sizeof(int));
        *a = i;

        if (i % 2 == 0)
        {
            doubly_linked_list_prepend(list, a);
        }
        else
        {
            doubly_linked_list_append(list, a);
        }
    }

    int a = 9;
    Node *r = doubly_linked_list_find(list, &a, int_equal);
    cr_assert_not_null(r, "doubly_linked_list_find() failed");

    doubly_linked_list_remove(list, r, true);
    cr_assert_eq(list->size, 9, "doubly_linked_list_remove() failed");

    doubly_linked_list_free(&list, true);
}

Test(doubly_linked_list_insert_before, test_doubly_linked_list_insert_before,
     .description = "Test inserting a node before another node in a doubly linked list.")
{
    DoublyLinkedList *list = doubly_linked_list_new();
    cr_assert_not_null(list, "doubly_linked_list_new() failed");

    for (int i = 0; i < 10; i++)
    {
        int *a = malloc(sizeof(int));
        *a = i;

        doubly_linked_list_append(list, a);
    }

    int a = 9;
    Node *r = doubly_linked_list_find(list, &a, int_equal);
    cr_assert_not_null(r, "doubly_linked_list_find() failed");

    int *b = malloc(sizeof(int));
    *b = 11;
    doubly_linked_list_insert_before(list, r, b);
    cr_assert_eq(list->size, 11, "doubly_linked_list_insert_before() failed");
    cr_assert_eq(list->tail->prev->data, b, "doubly_linked_list_insert_before() failed");

    doubly_linked_list_free(&list, true);
}

Test(doubly_linked_list_insert_after, test_doubly_linked_list_insert_after,
     .description = "Test inserting a node after another node in a doubly linked list.")
{
    DoublyLinkedList *list = doubly_linked_list_new();
    cr_assert_not_null(list, "doubly_linked_list_new() failed");

    for (int i = 0; i < 10; i++)
    {
        int *a = malloc(sizeof(int));
        *a = i;

        doubly_linked_list_append(list, a);
    }

    int a = 5;
    Node *r = doubly_linked_list_find(list, &a, int_equal);
    cr_assert_not_null(r, "doubly_linked_list_find() failed");

    int *b = malloc(sizeof(int));
    *b = 51;
    doubly_linked_list_insert_after(list, r, b);
    cr_assert_eq(list->size, 11, "doubly_linked_list_insert_after() failed");
    cr_assert_eq(r->next->data, b, "doubly_linked_list_insert_after() failed");

    doubly_linked_list_free(&list, true);
}

Test(doubly_linked_list_iterator, test_doubly_linked_list_iterator,
     .description = "Test iterating over a doubly linked list.")
{
    DoublyLinkedList *list = doubly_linked_list_new();

    for (int i = 0; i < 10; i++)
    {
        int *a = malloc(sizeof(int));
        *a = i;

        doubly_linked_list_append(list, a);
    }

    DoublyLinkedListIterator *it = doubly_linked_list_iterator(list);
    cr_assert_not_null(it, "doubly_linked_list_iterator() failed");

    int i = 0;
    while (doubly_linked_list_iterator_has_next(it))
    {
        NodeData data = doubly_linked_list_iterator_data(it);
        cr_assert_eq(*(int *)data, i, "doubly_linked_list_iterator() failed");
        doubly_linked_list_iterator_next(it);
        i++;
    }

    doubly_linked_list_free_iterator(&it);
    cr_assert_null(it, "doubly_linked_list_free_iterator() failed");

    doubly_linked_list_free(&list, true);
}
