#ifndef __IO_H__

#define __IO_H__

#include "data_structures.h"
#include "constants.h"
#include "vector_queue.h"
#include "list_queue.h"

int fill_vdata(vector_q *vector, const int number);

int del_vdata(vector_q *vector);

int fill_ldata(node_t **tail, const int number);

int del_ldata(node_t **tail);

int print_vdata(vector_q *vector);

int print_ldata(node_t **tail);

uint64_t tick(void);

void info(void);

void menu(void);

void print_error(const int exit_code);

#endif // __IO_H__
