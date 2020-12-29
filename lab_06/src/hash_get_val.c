#include "../inc/hash_get_val.h"

int hash_get_val(lnode_t **table, const int key, const int val, \
                int cmpc, int *counter, const int pflag)
{
    int res;
    lnode_t *tempp = table[key];

    for (; table[key] && table[key]->field != val && cmpc > 0; \
        table[key] = table[key]->next)
    {
        (*counter)++;
        cmpc--;
        if (pflag == 1)
            printf("[%d] --> ", table[key]->field);
    }

    if (table[key] != NULL)
        res = table[key]->field;

    if (table[key] && cmpc > 0)
    {
        table[key] = tempp;
        return res;
    }
    else if (table[key] == NULL && cmpc > 0)
    {
        table[key] = tempp;
        return EMPTY_FIELD;
    }
    else
    {
        table[key] = tempp;
        return NUMBER_COMPARE_ERROR;
    }
}
