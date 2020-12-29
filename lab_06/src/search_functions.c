#include "../inc/search_functions.h"

uint64_t tick(void)
{
    uint32_t high, low;
    __asm__ __volatile__(
        "rdtsc\n"
        "movl %%edx, %0\n"
        "movl %%eax, %1\n"
        : "=r"(high), "=r"(low)::"%rax", "%rbx", "%rcx", "%rdx");

    uint64_t ticks = ((uint64_t)high << 32) | low;

    return ticks;
}

int file_search(FILE *tree_file, const int val)
{
    rewind(tree_file);

    int flag = 0;
    int cmpc = 1;
    uint64_t start = tick(), end;

    for (int rc, numb; (rc = fscanf(tree_file, "%d", &numb)) != EOF; cmpc++)
    {
        if (rc != 1)
            return FILE_READING_ERROR;

        if (numb == val)
        {
            end = tick();
            flag = 1;
            break;
        }
    }

    if (flag == 1)
    {
        printf("\n\x1B[32mФайл:\x1B[0m\n");

        printf("Время поиска элемента: %llu\n", end - start);

        fseek(tree_file, 0, SEEK_END);
        long size = ftell(tree_file);

        printf("Объем занимаемой памяти: %ld\n", size);

        printf("Количество сравнений для поиска элемента: %d\n", cmpc);
    }
    else
        return EMPTY_FIELD;

    return OK;
}

tnode_t *tree_traversal(tnode_t *root, const int val, int *cmpc, int *eflag)
{
    (*cmpc)++;

    if (root == NULL)
        return NULL;
    else if (val < root->field)
        root->left = tree_traversal(root->left, val, cmpc, eflag);
    else if (val > root->field)
        root->right = tree_traversal(root->right, val, cmpc, eflag);
    else
        *eflag = 1;

    return root;
}

int tree_search(tnode_t *root, const int val, char *const tname, FILE *tree_file)
{
    int eflag = 0;
    int cmpc = -1;
    uint64_t start = tick(), end;

    tree_traversal(root, val, &cmpc, &eflag);

    if (eflag == 0)
        return EMPTY_FIELD;
    
    end = tick();

    if (strcmp(tname, "ДДП") == 0)
        printf("\n\x1B[32mДвоичное дерево поиска:\x1B[0m\n");
    if (strcmp(tname, "АВЛ") == 0)
        printf("\n\x1B[32mАВЛ дерево:\x1B[0m\n");

    printf("Время поиска элемента: %llu\n", end - start);

    int size = 0;

    rewind(tree_file);

    for (int rc, numb; (rc = fscanf(tree_file, "%d", &numb)) != EOF; size++)
    {
        if (rc != 1)
            return FILE_READING_ERROR;
    }

    printf("Объем занимаемой памяти: %ld\n", size * sizeof(tnode_t));

    printf("Количество сравнений для поиска элемента: %d\n", cmpc + 1);

    return OK;
}

int hash_table_search(lnode_t **hash_table, const int key, const int val, int cmpc, const int size)
{
    int counter = 0;
    uint64_t start = tick(), end;

    for (int i = 0; i < 100; i++)
    {
        hash_get_val(hash_table, key, val, cmpc, &counter, 0);
    }

    end = tick();

    printf("\n\x1B[32mХэш-таблица:\x1B[0m\n");

    printf("Время поиска элемента: %llu\n", (end - start) / 100);

    printf("Объем занимаемой памяти: %ld\n", size * sizeof(lnode_t));

    counter = 1;

    hash_get_val(hash_table, key, val, cmpc, &counter, 0);

    printf("Количество сравнений для поиска элемента: %d\n", counter);

    return OK;
}


