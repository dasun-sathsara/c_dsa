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

typedef void (*HashTableKeyFreeFunction)(HashTableKey);

typedef void (*HashTableValueFreeFunction)(HashTableValue);

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
    size_t size;

    HashFunction hash_function;
    EqualityFunction equality_function;
    HashTableKeyFreeFunction key_free_function;
    HashTableValueFreeFunction value_free_function;
};

/**
 * @brief Creates a new hash table. The hash table will use the given hash function and equality function to manage the
 keys.
 *
 * @param size The number of buckets in the hash table.
 * @param hash_function The hash function to use to hash the keys.
 * @param equality_function The equality function to use to compare keys.
 * @return A pointer to the new hash table.
 */
HashTable *hash_table_new(size_t size, HashFunction hash_function, EqualityFunction equality_function);

#endif // HASH_TABLE_H
