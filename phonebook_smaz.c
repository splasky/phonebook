#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "phonebook_smaz.h"
#include "smaz/smaz.h"

/* original version */
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
    e->pNext = (entry*)malloc(sizeof(entry));
    e = e->pNext;
    smaz_compress(lastName, strlen(lastName), e->lastName, sizeof(e->lastName));
    e->pNext = NULL;

    return e;
}
