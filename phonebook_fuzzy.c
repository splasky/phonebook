#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "fuzzy.h"
#include "phonebook_orig.h"

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
    strcpy(e->lastName, lastName);
    e->pNext = NULL;

    return e;
}

char* fuzzyFind(char* str, entry* pHead, int similarity)
{

    while (pHead != NULL) {
        char* word = pHead->lastName;
        // Match
        if (strcasecmp(str, word) == 0) {
            return word;
        }

        int score = LevenshteinDistance(str, strlen(str), word, strlen(word));

        // Match?
        if (score <= similarity) {
            printf("%s\n", pHead->lastName);
        }

        pHead = pHead->pNext;
    }

    /* printf("No result for %s,Did you mean: %s\n", str, maybe); */
    return NULL;
}
