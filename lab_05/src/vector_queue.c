#include "../inc/vector_queue.h"

int vpush(vector_q *vector, const int val)
{
    if (vector == NULL)
        return NULL_POINTER;

    if (vector->lelp >= QUEUE_SIZE)
        return QUEUE_OVERFLOW;

    vector->data[vector->lelp] = val;
    vector->lelp++;

    return OK;
}

int vpop(vector_q *vector)
{
    if (vector == NULL)
        return NULL_POINTER;

    if (vempty(vector) == QUEUE_EMPTY)
        return QUEUE_UNDERFLOW;
        
    return vector->data[vector->felp++ - 1];
}

int vpeek(vector_q *vector)
{
    if (vector == NULL)
        return NULL_POINTER;

    if (vempty(vector) == QUEUE_EMPTY)
        return QUEUE_UNDERFLOW;

    return vector->data[vector->felp - 1];
}

int vempty(vector_q *vector)
{
    if (vector == NULL)
        return NULL_POINTER;

    if (vector->lelp < vector->felp)
        return QUEUE_EMPTY;

    return OK;
}

int vcopy(vector_q *vector, vector_q *vector_copy, vector_q *vector_temp)
{
    vector_init(vector_copy);
    vector_init(vector_temp);

    for (; vempty(vector) == OK; vpop(vector))
    {
        if (vpush(vector_temp, vpeek(vector)) != OK)
            return QUEUE_OVERFLOW;
    }

    vector->felp = 1;
    vector->lelp = 0;

    for (; vempty(vector_temp) == OK; vpop(vector_temp))
    {
        if (vpush(vector, vpeek(vector_temp)) != OK)
            return QUEUE_OVERFLOW;
        if (vpush(vector_copy, vpeek(vector_temp)) != OK)
            return QUEUE_OVERFLOW;
    }

    return OK;
}
