#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "phonebook_fuzzy.h"
#define DICT_FILE "./dictionary/words.txt"

int main(int argc, char* argv[])
{
    FILE* fp;
    int i = 0;
    char line[MAX_LAST_NAME_SIZE];

    /* check file opening */
    fp = fopen(DICT_FILE, "r");
    if (fp == NULL) {
        printf("cannot open the file\n");
        return -1;
    }

    /* build the entry */
    entry *pHead, *e;
    pHead = (entry*)malloc(sizeof(entry));
    printf("size of entry : %zu bytes\n", sizeof(entry));
    e = pHead;
    e->pNext = NULL;

    while (fgets(line, sizeof(line), fp)) {
        while (line[i] != '\0')
            i++;
        line[i - 1] = '\0';
        i = 0;
        e = append(line, e);
    }

    /* close file as soon as possible */
    fclose(fp);

    /* the givn last name to find */
    char input[MAX_LAST_NAME_SIZE] = "splasky";
    fuzzyFind(input, pHead, 5);

    /* compute the execution time */
    while (pHead->pNext) {
        entry* cur = pHead->pNext;
        free(pHead);
        pHead = cur;
    }
    free(pHead);
    return 0;
}
