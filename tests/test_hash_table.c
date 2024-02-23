#include <criterion/criterion.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../src/arraylist.h"
#include "../src/doubly_linked_list.h"
#include "../src/hash_table.h"
#include "../src/hashing_functions.h"

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

// string key, int value
void f_string_int(NodeData data)
{
    KeyValuePair *kvp = (KeyValuePair *)data;
    free(kvp->key);
    free(kvp);
}

// string key, string value
void f_string_string(NodeData data)
{
    KeyValuePair *kvp = (KeyValuePair *)data;
    free(kvp->key);
    free(kvp->value);
    free(kvp);
}

bool string_equal(NodeData a, NodeData b)
{
    KeyValuePair *kvp_a = (KeyValuePair *)a;
    KeyValuePair *kvp_b = (KeyValuePair *)b;
    return strcmp(kvp_a->key, kvp_b->key) == 0;
}

char *strdup(const char *str)
{
    size_t len = strlen(str) + 1; // +1 for the null terminator
    char *new_str = malloc(len);
    if (new_str == NULL)
    {
        return NULL; // Handle allocation failure
    }
    strcpy(new_str, str);
    return new_str;
}

void print_hash_table(HashTable *hash_table)
{
    printf("\n");
    printf("[");
    for (size_t i = 0; i < hash_table->buckets->capacity; i++)
    {
        DoublyLinkedList *bucket = hash_table->buckets->items[i];
        if (bucket->size == 0)
        {
            printf(" X ");
        }
        else
        {
            printf(" %ld ", bucket->size);
        }
    }
    printf("]\n\n");
}

Test(hash_table, test_hash_table_insert_and_retrieve, .description = "Test insertion and retrieval of key-value pairs")
{
    HashTable *hash_table = hash_table_new(10, string_hash, string_equal, f_string_int);
    cr_assert_not_null(hash_table, "hash_table_new() failed");

    char *key = strdup("key");
    int value = 10;

    cr_assert(hash_table_insert(hash_table, key, &value), "hash_table_insert() failed");

    int *retrieved_value = hash_table_search(hash_table, key);
    cr_assert_not_null(retrieved_value, "hash_table_search() failed");
    cr_assert_eq(*retrieved_value, value, "hash_table_search() failed");
    hash_table_free(hash_table);
}

Test(hash_table, test_hash_table_insert_large, .description = "Test insertion of a large number of key-value pairs")
{
    HashTable *hash_table = hash_table_new(300, string_hash, string_equal, f_string_int);
    cr_assert_not_null(hash_table, "hash_table_new() failed");

    for (size_t i = 0; i < 300; i++)
    {
        // random string for key
        char *key = malloc(10);
        sprintf(key, "key%ld", i);

        int *value = malloc(sizeof(int));
        *value = i * 2;
        hash_table_insert(hash_table, key, value);
    }

    int *rv = hash_table_search(hash_table, "key299");
    cr_assert_not_null(rv, "hash_table_search() failed");
    cr_assert_eq(*rv, 598, "hash_table_search() failed");

    hash_table_free(hash_table);
}

Test(hash_table, test_hash_table_remove, .description = "Test removing a key-value pair from the hash table")
{
    HashTable *hash_table = hash_table_new(100, string_hash, string_equal, f_string_int);
    cr_assert_not_null(hash_table, "hash_table_new() failed");

    for (size_t i = 0; i < 100; i++)
    {
        // random string for key
        char *key = malloc(10);
        sprintf(key, "%ldkey", i);

        int *value = malloc(sizeof(int));
        *value = i * 2;
        hash_table_insert(hash_table, key, value);
    }

    int *rv = hash_table_search(hash_table, "99key");
    cr_assert_not_null(rv, "hash_table_search() failed");

    cr_assert(hash_table_remove(hash_table, "99key"), "hash_table_remove() failed");

    rv = hash_table_search(hash_table, "99key");
    cr_assert_null(rv, "hash_table_search() failed");

    hash_table_free(hash_table);
}

void print_hash_table_entry(KeyValuePair *kvp)
{

    printf("(%s, %d)\n", (char *)kvp->key, *(int *)kvp->value);
}

Test(hash_table, hash_table_iterator, .description = "Test the hash table iterator")
{
    HashTable *hash_table = hash_table_new(25, string_hash, string_equal, f_string_int);
    cr_assert_not_null(hash_table, "hash_table_new() failed");

    for (size_t i = 0; i < 25; i++)
    {
        // random string for key
        char *key = malloc(10);
        sprintf(key, "key%ld", i);

        int *value = malloc(sizeof(int));
        *value = i * 2;
        hash_table_insert(hash_table, key, value);
    }

    HashTableIterator *iterator = hash_table_iterator_new(hash_table);
    cr_assert_not_null(iterator, "hash_table_iterator_new() failed");
    cr_assert_eq(iterator->bucket_index, -1, "hash_table_iterator_new() failed");

    size_t i = 0;
    while (hash_table_iterator_has_next(iterator) == true)
    {
        hash_table_iterator_next(iterator);
        KeyValuePair *kvp = hash_table_iterator_get(iterator);
        cr_assert_not_null(kvp, "hash_table_iterator_get() failed");
        i++;
    }

    cr_assert_eq(i, 25, "hash_table_iterator_has_next() failed");

    hash_table_iterator_free(iterator);
    hash_table_free(hash_table);
}
