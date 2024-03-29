#include "hash_table.h"
#include "arraylist.h"
#include "doubly_linked_list.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

HashTable *hash_table_new(size_t size, HashFunction hash_function, EqualityFunction equality_function,
                          KeyValuePairFreeFunction kvp_free_function)
{
    HashTable *new_hash_table = malloc(sizeof(HashTable));

    if (new_hash_table == NULL)
    {
        perror("Failed to allocate memory for new HashTable");
        return NULL;
    }

    new_hash_table->hash_function = hash_function;
    new_hash_table->equality_function = equality_function;
    new_hash_table->kvp_free_function = kvp_free_function;

    // buckets is an arraylist of doubly linked lists
    new_hash_table->buckets = arraylist_new(size, NULL);

    // Initialize the number of entries to 0
    new_hash_table->num_of_entries = 0;

    if (new_hash_table->buckets == NULL)
    {
        perror("Failed to allocate memory for HashTable buckets");
        free(new_hash_table);
        return NULL;
    }

    // Initialize each bucket with a doubly linked list
    for (size_t i = 0; i < size; i++)
    {
        new_hash_table->buckets->items[i] = doubly_linked_list_new(kvp_free_function);
    }

    return new_hash_table;
}

void hash_table_free(HashTable *hash_table)
{
    if (hash_table == NULL)
    {
        return;
    }

    for (size_t i = 0; i < hash_table->buckets->size; i++)
    {
        DoublyLinkedList *bucket = hash_table->buckets->items[i];
        doubly_linked_list_free(bucket);
    }

    arraylist_free(hash_table->buckets);
    free(hash_table);
}

bool hash_table_insert(HashTable *hash_table, HashTableKey key, HashTableValue value)
{
    if (hash_table == NULL)
    {
        return false;
    }

    size_t index = hash_table->hash_function(key) % hash_table->buckets->capacity;

    // Get the bucket at the index
    DoublyLinkedList *bucket = hash_table->buckets->items[index];

    // Create a new key-value pair
    KeyValuePair *new_key_value_pair = malloc(sizeof(KeyValuePair));

    if (new_key_value_pair == NULL)
    {
        perror("Failed to allocate memory for new KeyValuePair");
        return false;
    }

    new_key_value_pair->key = key;
    new_key_value_pair->value = value;

    if (doubly_linked_list_append(bucket, new_key_value_pair) == false)
    {
        /*
        If the key-value pair was not added to the doubly linked list, free the memory allocated for the key-value pair
        */
        hash_table->kvp_free_function(new_key_value_pair);
        return false;
    }

    hash_table->num_of_entries++;

    return true;
}

HashTableValue hash_table_search(HashTable *hash_table, HashTableKey key)
{
    if (hash_table == NULL)
    {
        return NULL;
    }

    size_t index = hash_table->hash_function(key) % hash_table->buckets->capacity;

    DoublyLinkedList *bucket = hash_table->buckets->items[index];

    // Construct a KeyValuePair with the key to search for
    KeyValuePair kvp;
    kvp.key = key;

    // Search for a node with the specified key in doubly linked list
    Node *r = doubly_linked_list_find(bucket, &kvp, hash_table->equality_function);

    if (r == NULL)
    {
        return NULL;
    }

    // Access the value of the key-value pair through the node data
    return ((KeyValuePair *)r->data)->value;
}

bool hash_table_remove(HashTable *hash_table, HashTableKey key)
{

    if (hash_table == NULL)
    {
        return false;
    }

    size_t index = hash_table->hash_function(key) % hash_table->buckets->capacity;

    DoublyLinkedList *bucket = hash_table->buckets->items[index];

    // Construct a KeyValuePair with the key to search for
    KeyValuePair kvp;
    kvp.key = key;

    // Search for a node with the specified key in doubly linked list
    Node *r = doubly_linked_list_find(bucket, &kvp, hash_table->equality_function);

    if (r == NULL)
    {
        return false;
    }

    if (doubly_linked_list_remove(bucket, r) == false)
    {
        return false;
    }

    hash_table->num_of_entries--;

    return true;
}

HashTableIterator *hash_table_iterator_new(HashTable *hash_table)
{
    if (hash_table == NULL)
    {
        return NULL;
    }

    HashTableIterator *new_iterator = malloc(sizeof(HashTableIterator));

    if (new_iterator == NULL)
    {
        perror("Failed to allocate memory for new HashTableIterator");
        return NULL;
    }

    new_iterator->bucket_index = -1;
    new_iterator->current_node = NULL;
    new_iterator->hash_table = hash_table;

    return new_iterator;
}

bool hash_table_iterator_has_next(HashTableIterator *iterator)
{
    if (iterator == NULL)
    {
        return false;
    }

    if (iterator->current_node != NULL && iterator->current_node->next != NULL)
    {
        return true;
    }
    else
    {
        for (size_t i = iterator->bucket_index + 1; i < iterator->hash_table->buckets->capacity; i++)
        {
            DoublyLinkedList *bucket = iterator->hash_table->buckets->items[i];
            if (bucket->head != NULL)
            {
                return true;
            }
        }
    }

    return false;
}

void hash_table_iterator_next(HashTableIterator *iterator)
{
    if (iterator == NULL)
    {
        return;
    }

    if (iterator->current_node != NULL && iterator->current_node->next != NULL)
    {
        iterator->current_node = iterator->current_node->next;
        return;
    }
    else
    {
        for (size_t i = iterator->bucket_index + 1; i < iterator->hash_table->buckets->capacity; i++)
        {
            DoublyLinkedList *bucket = iterator->hash_table->buckets->items[i];
            if (bucket->head != NULL)
            {
                iterator->bucket_index = i;
                iterator->current_node = bucket->head;
                return;
            }
        }
    }
}

KeyValuePair *hash_table_iterator_get(HashTableIterator *iterator)
{

    if (iterator == NULL)
    {
        return NULL;
    }

    return iterator->current_node->data;
}

void hash_table_iterator_free(HashTableIterator *iterator)
{
    free(iterator);
}
