// linked_string.c
// ------------
// Simple program that represent strings as a linked list of chars.
// It takes arguments from the command line and print using this method.
// ------------
// Created by Oz Tamir on 4/9/15.
// ------------

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define a boolean type
typedef char bool;
#define true 1
#define false 0

// Node in the linked list
typedef struct node{
    // Each node is a letter in a string
    char info;
    // Pointer to the next node in the list
    struct node* next;
} node_t;

void print_list(node_t* head, bool newline){
    /*
     * Print a linked list.
     */

    node_t* current = head;

    // While we still have nodes in the list
    while (current != NULL){
        // If the user want to print a newline after each node
        if (newline)
            printf("%c\n", current->info);
        else
            printf("%c", current->info);
        // Move on to the next node
        current = current->next;
    }
    // If the last char didn't caused a newline, print one
    if (!newline)
        printf("\n");
}

void push(node_t* head, char val){
    /*
     * Push a new node to a linked list.
     */

    // Assign the head pointer to a temporary pointer
    node_t* current = head;

    // Find the last node in the list
    while (current->next != NULL) {
        current = current->next;
    }

    // Allocate the next node
    current->next = malloc(sizeof(node_t));
    // Assign the passed value to the next node in the list
    current->next->info = val;
    current->next->next = NULL;
}

node_t* string_list(char* string){
    /*
     * Create a linked list to represent a string.
     */
    char* current = string;

    // Create the head of the list
    node_t* head = malloc(sizeof(node_t));
    head->info = *current;
    head->next = NULL;

    // Iterate over the string and push the characters into the list
    for (int i = 1; i < strlen(string); i++){
        push(head, *(current + i));
    }
    return head;

}

int main_linked_string(int argc, char** argv){
    // Create a pointer that will aid us when we create lists
    node_t *head;

    // Iterate over the command line arguments and print each and every one of them using a linked list of chars
    for (int i = 1; i < argc; i++) {
        // Create the list that represent the above string
        head = string_list(argv[i]);
        // Print the list
        print_list(head, false);
        // Release the memory
        free(head);
    }

    return 0;
}