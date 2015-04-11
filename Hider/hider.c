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

char* create_secret(char* secret_file){
    /*
     * Create a string that hides the file's content
     */
    FILE* secret_fp;
    char secret[SECRET_SIZE];

    // Open the file
    secret_fp = fopen(secret_file, "r");
    if (secret_fp == NULL) {
        fprintf(stderr, "Can't open secret file %s!\n", secret_file);
        exit(1);
    }

    // Read its content
    fgets(secret, SECRET_SIZE, secret_fp);
    fclose(secret_fp);

    // "Encrypt" (as if) the data
    xor_data(secret, DEFAULT_KEY);

    return secret;
}

char* read_secret(char* filename){
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
    fgets(encrypted, size + 1, fp);
    xor_data(encrypted, DEFAULT_KEY);

    // Close the file
    fclose(fp);

    return encrypted;
}

void write_data(FILE* out_fp, char* data, bool checksum){
    /*
     * Write data to file
     */
    // Write it to the file
    fputs(data, out_fp);
    // If requested, add up to 10 chars declaring the length of the data
    if (checksum)
        fprintf(out_fp, "%010d", (int)strlen(data));
}

void hide(char* img_file, char* secret_file) {
    /*
     * Hide a data from secret_file in img_file
     */
    FILE *img_fp;

    // Open the file
    img_fp = fopen(img_file, "ab");
    if (img_fp == NULL) {
        fprintf(stderr, "Can't open image file %s!\n", img_file);
        exit(1);
    }

    // Get the secret as a string
    char* secret = create_secret(secret_file);

    // Write the data to the file
    write_data(img_fp, secret, true);

    // Close the file
    fclose(img_fp);

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
    char* secret = read_secret(input_file);
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
