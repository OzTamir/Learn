//
// Created by Oz Tamir on 4/13/15.
//

#ifndef LEARN_MACROS_H
#define LEARN_MACROS_H

#include <stdio.h>

typedef void (*m_callback)(void* arg);

/* Open files, Python style */
#define m_with(filename, permission, code) \
   FILE* file = fopen(filename, permission); \
   if (file == NULL) { \
        fprintf(stderr, "Can't open file %s!\n", filename);\
        exit(1);\
    }\
    code\
    fclose(file);

/* Allocate memory, with callback function in case of an error */
#define m_malloc(buff, size_t, callback, callback_args) \
    if ((buff = malloc(size_t)) == NULL){\
        callback(callback_args);\
    }

/* Temporery allocate memory and release it afterwards */
#define m_tmalloc(memsize, code) \
    void* mem;\
    m_malloc(mem, memsize, , NULL);\
    code\
    free(mem);

int test_macros();
#endif //LEARN_MACROS_H
