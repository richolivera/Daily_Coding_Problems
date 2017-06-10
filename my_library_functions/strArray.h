#ifndef STRARRAY_H
#define STRARRAY_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_INPUT_STRING_LENGTH 160

typedef struct strArray
{
    uint32_t numTerms;
    char * term[MAX_INPUT_STRING_LENGTH/2]
} strArray_t;
#endif
