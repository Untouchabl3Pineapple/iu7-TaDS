#ifndef __VECTOR_QUEU_H__

#define __VECTOR_QUEU_H__

#include <stdio.h>

#include "data_structures.h"
#include "constants.h"
#include "memory_functions.h"

int vpush(vector_q *vector, const int val);

int vpop(vector_q *vector);

int vpeek(vector_q *vector);

int vempty(vector_q *vector);

int vcopy(vector_q *vector, vector_q *vector_copy, vector_q *vector_temp);

#endif // __VECTOR_QUEU_H__
