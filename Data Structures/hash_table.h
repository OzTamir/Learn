// hash_table.h
// ------------
// Simple Hash Table implantation in C.
// ------------
// Created by Oz Tamir on 4/10/15.
// ------------
//

#ifndef LEARN_HASH_TABLE_H
#define LEARN_HASH_TABLE_H

// Data type - an item in the dictionary can be of most types
typedef union{
    int i;
    float f;
    char c;
    char* s;
} data_t;

// Entry in the table
typedef struct entry_s{
    char* key;
    data_t* value;
    // We use separate chaining for collision handling
    struct entry_s* next;
} entry_t;

// A HashTable type
typedef struct{
    entry_t** _table;
    int _size;
    int size;
} HashTable;

// Create a new hash table
HashTable* create_table(int size);
// Expend a table to allow for more entries
void expend_table(HashTable* table);
// The hashing function
unsigned long hash(char* key);

// Create an entry for a key-value pair
entry_t* create_entry(char* key, data_t* value);

// Set a value for a given key
void set(HashTable *table, char* key, data_t* value);
// Retrieve the value of a key
data_t* get(HashTable *table, char *key);
// Deallocate a table
void delete_table(HashTable* table);

int main_hash_table();

#endif //LEARN_HASH_TABLE_H
