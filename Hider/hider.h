//
// Created by Oz Tamir on 4/11/15.
//
#include "../utils.h"

#ifndef LEARN_HIDER_H
#define LEARN_HIDER_H

/* CHANGE THIS KEY */
#define DEFAULT_KEY 4590
#define SECRET_SIZE 2048

void hide(char* img_file, char* secret_file);
void reveal(char* input_file, char* output_file);
int main_hider(int argc, char** argv);

void write_data(FILE* out_fp, char* data, bool checksum);
char* read_secret(char* filename);
char* create_secret(char* secret_file);
void xor_data(char *buff, int key);

#endif //LEARN_HIDER_H
