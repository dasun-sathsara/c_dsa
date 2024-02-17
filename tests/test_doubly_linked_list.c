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
    Node *current = list->head;
    printf("------------------\n");
    while (current != NULL)
    {
        printf("%d\n", *(int *)current->data);
        current = current->next;
    }
    printf("------------------\n");
}

Test(doubly_linked_list_search, test_doubly_linked_list_search,
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
    bool r = doubly_linked_list_search(list, &a, int_equal);
    cr_assert_eq(r, true, "doubly_linked_list_search() failed");

    doubly_linked_list_free(&list, true);
}

Test(doubly_linked_list_remove, test_doubly_linked_list_remove,
     .description = "Test removing a node from a doubly linked list.")
{
    DoublyLinkedList *list = doubly_linked_list_new();
    cr_assert_not_null(list, "doubly_linked_list_new() failed");

    int a = 1;
    int b = 2;

    int r = doubly_linked_list_remove(list, &a, int_equal, false);
    cr_assert_eq(r, false, "doubly_linked_list_remove() failed");

    doubly_linked_list_append(list, &a);
    r = doubly_linked_list_remove(list, &a, int_equal, false);
    cr_assert_eq(r, true, "doubly_linked_list_remove() failed");

    int c = 4;
    doubly_linked_list_append(list, &b);
    doubly_linked_list_append(list, &c);
    r = doubly_linked_list_remove(list, &b, int_equal, false);
    cr_assert_eq(r, true, "doubly_linked_list_remove() failed");

    int d = 23, e = 24, f = 25;
    doubly_linked_list_append(list, &d);
    doubly_linked_list_append(list, &e);
    doubly_linked_list_append(list, &f);

    int j = doubly_linked_list_search(list, &f, int_equal);
    cr_assert_eq(j, true, "doubly_linked_list_search() failed");
    doubly_linked_list_remove(list, &f, int_equal, false);
    j = doubly_linked_list_search(list, &f, int_equal);
    cr_assert_eq(j, false, "doubly_linked_list_search() failed");

    doubly_linked_list_free(&list, false);
}
