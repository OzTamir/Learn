//
// Created by Oz Tamir on 4/13/15.
//

#include <stdlib.h>
#include <string.h>
#include "macros.h"

void mmalloc_callback(void* args){
    printf("Error allocating memory.\n");
    if (args != NULL)
        printf("Detalis: %s", (char *)args);
}

void test_mtmalloc(){
    m_callback cb = &mmalloc_callback;
    char* thing = "hello";
    m_tmalloc(strlen(thing),
        strcpy(mem, thing);
        printf(mem);
    )
}

void test_mmalloc(){
    char* buff;
    m_callback cb = &mmalloc_callback;
    char* thing = "hello";
    m_malloc(buff, strlen(thing), cb, NULL)
    strcpy(buff, thing);
    printf(buff);
}

void test_with(){
    m_with("test.txt", "a+",
         char buff[100];
         fgets(buff, 4, file);
         if (strlen(buff) > 0)
             printf("File's content: %s\n", buff);
         fprintf(file, "TEST\n");
    )
}

int test_macros(){
    test_mtmalloc();
    return 0;
}