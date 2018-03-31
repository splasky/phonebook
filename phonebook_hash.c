#include <stdlib.h>
#include <string.h>
#include <strings.h>

#include "phonebook_hash.h"

entry* findName(
    char lastName[], entry* table[], hash_function func, unsigned int hash_table_size)
{
    unsigned hash_result = hash(lastName, func, hash_table_size);
    entry* pHead = table[hash_result];
    while (pHead) {
        if (strcasecmp(lastName, pHead->lastName) == 0) {
            return pHead;
        }
        pHead = pHead->pNext;
    }
    /* find nothing */
    return NULL;
}

void append(
    char lastName[], entry* table[], hash_function func, unsigned int hash_table_size)
{
    unsigned hash_result = hash(lastName, func, hash_table_size);
    entry* e = (entry*)malloc(sizeof(entry));
    e->pNext = NULL;
    e->pLast = NULL;
    if (!table[hash_result]) {
        table[hash_result] = e;
        e->pLast = e;
    } else {
        /* find empty space */
        entry* p = table[hash_result];
        p->pLast->pNext = e;
        p->pLast = e;
    }
    strcpy(e->lastName, lastName);
}

void initHashTable(entry* table[], unsigned int hash_table_size)
{
    for (int i = 0; i < hash_table_size; ++i) {
        table[i] = NULL;
    }
}
