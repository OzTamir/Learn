// hash_table.h
// ------------
// Simple Hash Table implantation in C.
// ------------
// Created by Oz Tamir on 4/10/15.
// ------------
//

/*
 * TODO:
 *  - Add collision handling
 *  - Add dynamic resizing
 */

#ifndef LEARN_HASH_TABLE_H
#define LEARN_HASH_TABLE_H

// Data type - an item in the dictionary can be of most types
typedef union{
    int i;
    float f;
    char c;
    char* s;
} data_t;

// A HashTable type
typedef struct{
    data_t* arr;
    int size;
} HashTable;

// Create a new hash table
HashTable* create_table(int size);
// The hashing function
int hash(char* key);

// Set a value for a given key
void set(HashTable *table, char* key, data_t value);
// Retrive the value of a key
data_t get(HashTable *table, char *key);

int main_hash_table();

#endif //LEARN_HASH_TABLE_H
