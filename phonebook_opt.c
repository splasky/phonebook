#include <stdlib.h>
#include <string.h>
#include <strings.h>

#include "avltree.h"
#include "mem_pool.h"
#include "phonebook_opt.h"
#include "smaz/smaz.h"

static m_pool* mem_pool = NULL;

static int Default_AVL_Compare(const void* a, const void* b)
{
    return strcasecmp(a, b);
}

entry* findName(char lastName[], AVLTreeNode* table[], hash_function func,
                unsigned int hash_table_size)
{
    char compressed[MAX_LAST_NAME_SIZE];
    memset(compressed, '\0', MAX_LAST_NAME_SIZE);
    smaz_compress(lastName, strlen(lastName), compressed, MAX_LAST_NAME_SIZE);
    unsigned int hash_result = hash(compressed, func, hash_table_size);

    AVLTreeNode* root = table[hash_result];
    void* data = AVLTreeFind(root, compressed);
    if (data)
        return (entry*)data;

    /* find nothing */
    return NULL;
}

void append(char lastName[], AVLTreeNode* table[], hash_function func,
            unsigned int hash_table_size)
{
    entry* e = (entry*)pool_access(mem_pool, sizeof(entry));
    smaz_compress(lastName, strlen(lastName), e->lastName, sizeof(e->lastName));
    unsigned int hash_result = hash(e->lastName, func, hash_table_size);

    if (!table[hash_result]) {
        AVLTreeNode* root = NULL;
        AVLTreeInsert(&root, e->lastName, e, Default_AVL_Compare);
        table[hash_result] = root;
    } else {
        /* find empty space */
        /* use avltree */
        AVLTreeInsert(&table[hash_result], e->lastName, e, Default_AVL_Compare);
    }
}

void initBigTable(AVLTreeNode* table[], unsigned int hash_table_size)
{
    mem_pool = pool_allocate(MEM_POOL_SIZE);
    for (int i = 0; i < hash_table_size; ++i) {
        table[i] = NULL;
    }
}
