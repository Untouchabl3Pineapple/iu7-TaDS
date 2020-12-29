#include "../inc/memory_functions.h"

tnode_t *tree_node_init(const int val, const int h)
{   
    tnode_t *node = (tnode_t *)malloc(sizeof(struct tnode_t));

    if (node)
    {
        node->field = val;
        node->height = h;
        node->left = NULL;
        node->right = NULL; 
    }

    return node;
}

lnode_t **hash_table_init(lnode_t **hash_table)
{
    hash_table = (lnode_t **) calloc(INT_MAX, sizeof(lnode_t *));

    return hash_table;
}

lnode_t *list_element_init(const int val)
{   
    lnode_t *node = (lnode_t *) malloc(sizeof(struct lnode_t));

    if (node)
    {
        (node)->field = val;
        (node)->next = NULL; 
    }

    return node;
}
