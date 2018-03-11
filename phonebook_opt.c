#include <stdlib.h>
#include <string.h>
#include <strings.h>

#include "phonebook_opt.h"

entry* findName(char lastName[], entry* table[], hash_function func)
{
    unsigned hash_result = hash(lastName, func);
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

void append(char lastName[], entry* table[], hash_function func)
{
    unsigned hash_result = hash(lastName, func);
    entry* e = (entry*)malloc(sizeof(entry));
    e->pNext = NULL;
    if (!table[hash_result]) {
        table[hash_result] = e;
    } else {
        /* find empty space */
        entry* p = table[hash_result];
        while (p->pNext) {
            p = p->pNext;
        }
        p->pNext = e;
    }
    strcpy(e->lastName, lastName);
}

unsigned hash(char* name, hash_function func)
{
    unsigned ret = func(name, strlen(name));
    return ret % HASH_TABLE_SIZE;
}

void initHashTable(entry* table[])
{
    for (int i = 0; i < HASH_TABLE_SIZE; ++i) {
        table[i] = NULL;
    }
}
