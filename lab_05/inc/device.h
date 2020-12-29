#ifndef __DEVICE_H__

#define __DEVICE_H__

#include <time.h>
#include <math.h>

#include "data_structures.h"
#include "constants.h"
#include "memory_functions.h"
#include "vector_queue.h"
#include "list_queue.h"

#define VECTOR_SIZE (queue->lelp - queue->felp + 1)

double get_time(const int left_limit, const int right_limit);

void vector_model(vector_q *queue,
                const int t1_in, const int t1_out,
                const int t2_in, const int t2_out);

#endif // __DEVICE_H__
