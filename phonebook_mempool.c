#include <stdlib.h>
#include <string.h>

#include "phonebook_opt.h"

/* TODO: FILL YOUR OWN IMPLEMENTATION HERE! */
entry* findName(char lastName[], entry* pHead)
{
    while (pHead != NULL) {
        if (strcasecmp(lastName, pHead->lastName) == 0)
            return pHead;
        pHead = pHead->pNext;
    }
    return NULL;
}

entry* append(char lastName[], entry* e)
{
    /* allocate memory for the new entry and put lastName */
    e->pNext = (entry*)pool_access(pool, sizeof(entry));
    e = e->pNext;
    strcpy(e->lastName, lastName);
    e->pNext = NULL;

    return e;
}
