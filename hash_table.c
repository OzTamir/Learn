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
    HashTable* table;
    table = malloc(sizeof(HashTable));
    table->arr = malloc(size * sizeof(data_t));
    table->size = size;
    return table;

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

void set(HashTable *table, char* key, data_t value) {
    /*
     * Set a value for a key in the table
     */
    // Calculate the hash
    int index = (hash(key) % table->size);
    // Set the item in this index
    table->arr[index] = value;
}

data_t get(HashTable *table, char *key) {
    /*
     * Retrieve an item from the table for a certain key
     */
    // Calculate the hash
    int index = (hash(key) % table->size);
    // Retrieve the item in this index
    return table->arr[index];
}

int main_hash_table() {
    // Create an HashTable with a size of 10
    HashTable* table = create_table(10);
    data_t data, res;

    // Set "Hello" = "World!" in the table
    printf("Setting \"Hello\" = \"World!\"\n");
    data.s = "World!";
    set(table, "Hello", data);

    // Get the value for key "Hello"
    res = get(table, "Hello");
    printf("Value for \"Hello\" = %s\n", res.s);

    // Set "Giddy" = "Mate!" in the table
    printf("Setting key \"Giddy\" = \"Mate!\"\n");
    data.s = "Mate!";
    set(table, "Giddy", data);

    // Get the value for key "Giddy"
    res = get(table, "Giddy");
    printf("Value for \"Giddy\" = %s\n", res.s);
    return 0;
}
