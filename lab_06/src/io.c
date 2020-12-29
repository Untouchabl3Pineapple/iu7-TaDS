#include "../inc/io.h"

tnode_t *add_tdnode(tnode_t *droot, const int val, int *h)
{
    (*h)++;

    if (droot == NULL)
        droot = tree_node_init(val, *h);
    else if (val < droot->field)
        droot->left = add_tdnode(droot->left, val, h);
    else
        droot->right = add_tdnode(droot->right, val, h);

    return droot;
}

tnode_t *add_tavlnode(tnode_t *avlroot, const int val, int *h)
{
	(*h)++;

    if (avlroot == NULL)
        avlroot = tree_node_init(val, *h);
    else if (val < avlroot->field)
        avlroot->left = add_tavlnode(avlroot->left, val, h);
    else
        avlroot->right = add_tavlnode(avlroot->right, val, h);

    return balance(avlroot);
}

int bin_tree_filling(tnode_t **droot, tnode_t **avlroot, FILE *tree_file)
{
    rewind(tree_file);

    for (int rc, val, h; (rc = fscanf(tree_file, "%d", &val)) != EOF;)
    {
        if (rc != 1)
            return FILE_READING_ERROR;

        h = -1;
        *droot = add_tdnode(*droot, val, &h);

        h = -1;
        *avlroot = add_tavlnode(*avlroot, val, &h);
    }

    return OK;
}

void tree_print(tnode_t *root, int space)
{
    int spacing = 5;

    if (root != NULL)
    {
        space += spacing;
        tree_print(root->right, space);

        printf("\n");

        for (int i = spacing; i < space; i++)
        {
            printf(" ");
        }

        printf("[%d]\n", root->field);

        tree_print(root->left, space);
    }
}

int hash_table_fill(lnode_t **hash_table, FILE *tree_file, int *max_ind, \
                    char *const filter)
{
    rewind(tree_file);

    for (int rc, val; (rc = fscanf(tree_file, "%d", &val)) != EOF;)
    {
        if (rc != 1)
            return FILE_READING_ERROR;

        if (strcmp(filter, "main") == 0)
        {
            lnode_t *node = list_element_init(val);

            node->next = hash_table[MAIN_KEY];
            hash_table[MAIN_KEY] = node;

            if (MAIN_KEY > *max_ind)
                *max_ind = MAIN_KEY;
        }
        else if (strcmp(filter, "spare") == 0)
        {
            lnode_t *node = list_element_init(val);

            node->next = hash_table[SPARE_KEY];
            hash_table[SPARE_KEY] = node;

            if (SPARE_KEY > *max_ind)
                *max_ind = SPARE_KEY;
        }
        else
            return HASH_TABLE_FILTER_ERROR;
    }

    return OK;
}

void hash_table_print(lnode_t **table, const int max_ind)
{
    for (int i = 0; i < max_ind + 1; i++)
    {
        lnode_t *tempp = table[i];
        printf("(%d)  ", i);
        for (; table[i]; table[i] = table[i]->next)
        {
            printf("[%d] --> ", table[i]->field);
            if (table[i]->next == NULL)
                printf("NULL");  
        }
        printf("\n");
        table[i] = tempp;
    }
}

