//
// Created by Oz Tamir on 4/10/15.
//

#include "main.h"

void usage(){
    /*
     * Print a usage message
     */
    printf("Usage: ./Learn filename args\n");
    printf("Available demos:\n");
    for (int i = 0; i < num_demos; i++)
        printf("%d - %s\n", i + 1, available[i]);
}

int main(int argc, char** argv){
    // If we didn't got a filename print a usage message
    if (argc < 2){
        usage();
        return 0;
    }

    // If the user is looking for the linked string demo, run it
    if (strcmp(argv[1], "linked_string.c") == 0)
        main_linked_string(argc, argv);
    // If the user is looking for the hash table demo, run it
    else if (strcmp(argv[1], "hash_table.c") == 0 || strcmp(argv[1], "hash_table.h") == 0)
        main_hash_table();
    // If the user is looking for the hiding demo
    else if (strcmp(argv[1], "hider.c") == 0 || strcmp(argv[1], "hider.h") == 0)
        main_hider(argc, argv);
    // Else, print a usage message
    else
        usage();
    return 0;
}