#ifndef __BALANCE_H__

#define __BALANCE_H__

#include "data_structures.h"

unsigned char height(tnode_t *p);

int bfactor(tnode_t *p);

void fixheight(tnode_t *p);

tnode_t *rotateright(tnode_t *p);

tnode_t *rotateleft(tnode_t *q);

tnode_t *balance(tnode_t *p);

#endif // __BALANCE_H__
