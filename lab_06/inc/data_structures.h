#ifndef __DATA_STRUCTURES_H__

#define __DATA_STRUCTURES_H__

#include <stdio.h>

#include "constants.h"

typedef struct tnode_t
{
    int field;
    unsigned char height;

    struct tnode_t *left;
    struct tnode_t *right;
} tnode_t;

typedef struct lnode_t
{
    int field;
    
    struct lnode_t *next;
} lnode_t;

#endif // __DATA_STRUCTURES_H__
