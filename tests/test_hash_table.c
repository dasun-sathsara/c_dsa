#include <criterion/criterion.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../src/arraylist.h"
#include "../src/doubly_linked_list.h"
#include "../src/hash_table.h"

Test(hash_table, test_hash_table_new, .description = "Test creation of a new hash table")
{
    HashTable *hash_table = hash_table_new(10, NULL, NULL, NULL);
    cr_assert_not_null(hash_table, "hash_table_new() failed");

    cr_assert_eq(hash_table->num_of_entries, 0, "hash_table_new() failed");

    // Assert the head of the first bucket is NULL
    DoublyLinkedList *bucket = hash_table->buckets->items[0];
    cr_assert_null(bucket->head, "hash_table_new() failed");

    // Assert the tail of the doubly linked list that is in the last bucket is NULL
    bucket = hash_table->buckets->items[hash_table->buckets->capacity - 1];
    cr_assert_null(bucket->tail, "hash_table_new() failed");

    hash_table_free(hash_table);
}
