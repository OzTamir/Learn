//
// Created by Oz Tamir on 4/11/15.
//
#include "Data Structures/linked_string.c"
#include "Data Structures/hash_table.h"
#include "Hider/hider.h"
#include "MacroUtils/macros.h"
#include "utils.h"

#ifndef LEARN_MAIN_H
#define LEARN_MAIN_H

static const int num_demos = 3;
static const char* available[num_demos] = {
        "Linked list",
        "Hash Tables",
        "Hider"
};

void usage();
int main(int argc, char** argv);

#endif //LEARN_MAIN_H
