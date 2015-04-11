// hash_table.c
// ------------
// Simple Hash Table implantation in C.
// ------------
// Created by Oz Tamir on 4/10/15.
// ------------
//

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "hash_table.h"

HashTable* create_table(int size){
    /*
     * Create a new hash table with the requested size.
     */
    HashTable* t;

    // Avoid logic errors
    if (size < 1)
        return NULL;

    // Allocate the table
    if ((t = malloc(sizeof(HashTable))) == NULL)
        return NULL;

    // Alocate pointer to head nodes
    if ((t->_table = malloc(size * sizeof(entry_t*))) == NULL)
        return NULL;

    // Initialize the entries to a NULL
    for (int i = 0; i < size; i++)
        t->_table[i] = NULL;

    // Set the table size
    t->size = size;

    return t;

}

int hash(char *key) {
    /*
     * A Simple hash function
     */
    int res = 1;
    for (int i = 0; i < strlen(key); i++){
        // Since a zero won't matter or it will ruin the counting, we ignore any zeros
        if ((int)key[i] != 0) {
            // Simply, if it's even multiply by it, else add it
            if (res % 2)
                res *= key[i];
            else
                res += key[i];
        }
    }

    // Since we are only adding and multiplying, we might get an int overflow - so we take care of it
    if (res < 0)
        res *= -1;
    return res;
}

entry_t* create_entry(char *key, data_t *value) {
    /*
     * Create an entry object for a key-value.
     */
    entry_t* entry;

    // Allocate the entry
    if ((entry = malloc(sizeof(entry_t))) == NULL)
        return NULL;

    // Assign the Key and the Value
    entry->key = key;
    entry->value = value;
    entry->next = NULL;

    return entry;
}

void set(HashTable *table, char* key, data_t* value) {
    /*
     * Set a value for a key in the table
     */
    entry_t* next = NULL;
    entry_t* last = NULL;

    // Create the entry
    entry_t* entry = create_entry(key, value);

    // Calculate the hash
    int index = (hash(key) % table->size);

    // Find the last chain in the table (remember: we are using separate chaining)
    next = table->_table[index];
    while (next != NULL && next->key != NULL && strcmp(key, next->key) > 0){
        last = next;
        next = next->next;
    }

    // Case 1: There is already a value for that key
    if (next != NULL && next->key != NULL && strcmp(key, next->key) == 0){
        free(next->value);
        next->value = value;
    }

    // Case 2: There isn't, and we need to add it
    else {
        // Case 2.1: We are at the start of the linked list
        if (next == table->_table[index]){
            entry->next = next;
            table->_table[index] = entry;
        }

        // Case 2.2: We are at the end
        else if (next == NULL){
            last->next = entry;
        }

        // Case 2.3: We are in the middle
        else {
            entry->next = next;
            last->next = entry;
        }
    }
}

data_t* get(HashTable *table, char *key) {
    /*
     * Retrieve an item from the table for a certain key
     */
    // Calculate the hash
    int index = (hash(key) % table->size);
    entry_t* entry;

    // Traverse the linked list
    entry = table->_table[index];
    while (entry != NULL && entry->key != NULL && strcmp(key, entry->key) > 0)
        entry = entry->next;

    // Check that we have a valid result
    if (entry == NULL || entry->key == NULL || strcmp(key, entry->key) != 0)
        return NULL;

    // Return what we found
    return entry->value;
}

int main_hash_table() {
    // Create an HashTable with a size of 10
    HashTable* table = create_table(10);
    data_t* data, *res;

    // Set "Hello" = "World!" in the table
    printf("Setting \"Hello\" = \"World!\"\n");
    data->s = "World!";
    set(table, "Hello", data);

    // Get the value for key "Hello"
    res = get(table, "Hello");
    printf("Value for \"Hello\" = %s\n", res->s);

    // Set "Giddy" = "Mate!" in the table
    printf("Setting key \"Giddy\" = \"Mate!\"\n");
    data->s = "Mate!";
    set(table, "Giddy", data);

    // Get the value for key "Giddy"
    res = get(table, "Giddy");
    printf("Value for \"Giddy\" = %s\n", res->s);
    return 0;
}

