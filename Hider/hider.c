// hider.c
// ------------
// Hide data inside files.
// ------------
// Created by Oz Tamir on 4/11/15.
// ------------
//

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "hider.h"

void xor_data(char *buff, int key) {
    /*
     * Encrypt a string
     */
    for (int i = 0; i < strlen(buff); i++)
        buff[i] = buff[i] ^ key;
}

secret_t* create_secret(char* secret_file){
    /*
     * Create a string that hides the file's content
     */
    FILE* secret_fp;
    char* buff;

    // Open the file
    secret_fp = fopen(secret_file, "rb");
    if (secret_fp == NULL) {
        fprintf(stderr, "Can't open secret file %s!\n", secret_file);
        exit(1);
    }

    // Determinate the size of the array required to store the data
    fseek(secret_fp, 0, SEEK_END);
    long size = ftell(secret_fp);
    rewind(secret_fp);
    // And alllocate that size
    if ((buff = malloc(size)) == NULL){
        fprintf(stderr, "Can't allocate memory for file.");
        exit(1);
    }

    // Read its content
    fread(buff, size, 1, secret_fp);
    fclose(secret_fp);

    // "Encrypt" (as if) the data
    xor_data(buff, DEFAULT_KEY);


    // Create the secret_t
    secret_t* secret = malloc(sizeof(secret_t));
    secret->size = size;
    secret->buff = buff;
    return secret;
}

secret_t* read_secret(char* filename){
    /*
     * Parse a secret message out of a file
     */
    FILE *fp = fopen(filename, "rb");
    if (fp == NULL){
        fprintf(stderr, "Can't open input file %s!\n", filename);
        exit(1);
    }

    // Change the pointer to the last 10 chars
    fseek(fp, -9, SEEK_END);

    // Get the last 10 chars
    char length[10];
    fgets(length, 10, fp);

    // Figure out the number of chars to read
    int size = atoi(length);

    // Change the pointer to the beginning of the encrypted data
    fseek(fp, -(size + 10), SEEK_END);

    // Allocate enough space for the data
    char* encrypted = malloc(size * sizeof(char));

    // Get the data and decrypt it
    fread(encrypted, size + 1, 1, fp);
    xor_data(encrypted, DEFAULT_KEY);

    // Close the file
    fclose(fp);

    // Create a secret_t struct and return it
    secret_t* secret = malloc(sizeof(secret_t));
    secret->size = size;
    secret->buff = encrypted;

    return secret;
}

void write_data(FILE* out_fp, secret_t* data, bool checksum){
    /*
     * Write data to file
     */
    // Write it to the file
    fwrite(data->buff, 1, data->size, out_fp);
    // If requested, add up to 10 chars declaring the length of the data
    if (checksum)
        fprintf(out_fp, "%032d", data->size);
}

void hide(char* output_file, char* secret_file) {
    /*
     * Hide a data from secret_file in img_file
     */
    FILE *out_fp;

    // Open the file
    out_fp = fopen(output_file, "ab");
    if (out_fp == NULL) {
        fprintf(stderr, "Can't open image file %s!\n", output_file);
        exit(1);
    }

    // Get the secret as a string
    secret_t* secret = create_secret(secret_file);

    // Write the data to the file
    write_data(out_fp, secret, true);

    // Free the memory to avoid leaks
    free(secret);

    // Close the file
    fclose(out_fp);

}

void reveal(char* input_file, char* output_file) {
    /*
     * Reveal secret data from input_file and write it into output_file
     */
    FILE *out_fp;

    // Open the output file for writing
    out_fp = fopen(output_file, "w+");
    if (out_fp == NULL) {
        fprintf(stderr, "Can't open output file %s!\n", output_file);
        exit(1);
    }

    // Read the secret data
    secret_t* secret = read_secret(input_file);
    // Write the data retrieved to the output file
    write_data(out_fp, secret, false);

    // Close the file
    fclose(out_fp);
}

void usage_hider(){
  /*
   * Print a usage message to the user
   */

    printf("Usage: hider key file1 file2 -d\n");
    printf("-d: Decrypt. The message from file1 will be written into file2.\n");
    printf("If the decrypt flag isn't passed, file2 will be embedded in file1.\n");
    printf("Please note that in order to decrypt you must use a valid key.\n");
};

/*
 * Since we run using main.c, we will have one more argument
 * Set this to 0 if running on its own
 */
#define LEARN_ARGC_FACTOR 1

int main_hider(int argc, char** argv){
    // In case we want to encrypt
    if (argc == (4 + LEARN_ARGC_FACTOR)){
        char* f_out = argv[2 + LEARN_ARGC_FACTOR];
        char* f_in = argv[3 + LEARN_ARGC_FACTOR];
        hide(f_out, f_in);
    }

    // In case we want to decrypt
    else if ((argc == 5 + LEARN_ARGC_FACTOR) && (strcmp(argv[4 + LEARN_ARGC_FACTOR], "-d") == 0)){
        char* f_in = argv[2 + LEARN_ARGC_FACTOR];
        char* f_out = argv[3 + LEARN_ARGC_FACTOR];
        reveal(f_in, f_out);
    }

    // In any other case
    else
        usage_hider();

    return 0;
}
