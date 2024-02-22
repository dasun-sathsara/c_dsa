#ifndef HASH_TABLE_H
#define HASH_TABLE_H

#include "arraylist.h"
#include "doubly_linked_list.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef void *HashTableKey;

typedef void *HashTableValue;

typedef struct _KeyValuePair KeyValuePair;

typedef struct _HashTable HashTable;

typedef unsigned long (*HashFunction)(HashTableKey);

typedef bool (*EqualityFunction)(HashTableKey, HashTableKey);

/*
Function pointer type for freeing the data(NodeData) in a node of the doubly linked list. Here, NodeData is a
KeyValuePair.
*/
typedef void (*KeyValuePairFreeFunction)(NodeData data);

// Structure to represent a key-value pair
struct _KeyValuePair
{
    HashTableKey key;
    HashTableValue value;
};

// Structure to represent a hash table
struct _HashTable
{
    ArrayList *buckets;
    size_t num_of_entries;

    HashFunction hash_function;
    EqualityFunction equality_function;
    KeyValuePairFreeFunction key_free_function;
};

/**
 * @brief Creates a new hash table. The hash table will use the given hash function and equality function to manage the
 keys.
 *
 * @param size The number of buckets in the hash table.
 * @param hash_function The hash function to use to hash the keys.
 * @param equality_function The equality function to use to compare keys.
 * @param kvp_free_function The function to free the key-value pairs in the hash table.
 * @return A pointer to the new hash table.
 */
HashTable *hash_table_new(size_t size, HashFunction hash_function, EqualityFunction equality_function,
                          KeyValuePairFreeFunction kvp_free_function);

/**
 * @brief Frees the memory allocated for a hash table.
 *
 * @param hash_table The hash table to be freed.
 */
void hash_table_free(HashTable *hash_table);

#endif // HASH_TABLE_H
