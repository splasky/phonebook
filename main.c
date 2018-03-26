#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include IMPL

#ifdef OPT
#define OUT_FILE "opt.txt"
#elif MEM_POOL
#define OUT_FILE "mempool.txt"
#else
#define OUT_FILE "orig.txt"
#endif

#define DICT_FILE "./dictionary/words.txt"

#ifdef HASH
#include "./hash_function.h"
hash_function default_hash_function = RSHash;
unsigned int HASH_TABLE_SIZE = 1009;
#elif MEM_POOL
#include "mem_pool.h"
m_pool* pool = NULL;
#define MEM_POOL_SIZE 100000000
#elif AVLTREE
#include "avltree.h"
#include "phonebook_avltree.h"
int Default_AVL_Compare(const void* a, const void* b)
{
    return strcasecmp(a, b);
}
#endif

static double diff_in_second(struct timespec t1, struct timespec t2)
{
    struct timespec diff;
    if (t2.tv_nsec - t1.tv_nsec < 0) {
        diff.tv_sec = t2.tv_sec - t1.tv_sec - 1;
        diff.tv_nsec = t2.tv_nsec - t1.tv_nsec + 1000000000;
    } else {
        diff.tv_sec = t2.tv_sec - t1.tv_sec;
        diff.tv_nsec = t2.tv_nsec - t1.tv_nsec;
    }
    return (diff.tv_sec + diff.tv_nsec / 1000000000.0);
}

int main(int argc, char* argv[])
{
    FILE* fp;
    int i = 0;
    char line[MAX_LAST_NAME_SIZE];
    struct timespec start, end;
    double cpu_time1, cpu_time2;

    /* check file opening */
    fp = fopen(DICT_FILE, "r");
    if (fp == NULL) {
        printf("cannot open the file\n");
        return -1;
    }

#ifdef HASH
    entry* hashTable[HASH_TABLE_SIZE];
    initHashTable(hashTable);
#elif MEM_POOL
    pool = pool_allocate(MEM_POOL_SIZE);
#elif AVLTREE
    AVLTreeNode* root = NULL;
#endif
    /* build the entry */
    entry *pHead, *e;
    pHead = (entry*)malloc(sizeof(entry));
    printf("size of entry : %zu bytes\n", sizeof(entry));
    e = pHead;
    e->pNext = NULL;
#if defined(__GNUC__)
    __builtin___clear_cache((char*)pHead, (char*)pHead + sizeof(entry));
#endif
    clock_gettime(CLOCK_REALTIME, &start);
    while (fgets(line, sizeof(line), fp)) {
        while (line[i] != '\0')
            i++;
        line[i - 1] = '\0';
        i = 0;
#ifdef HASH
        append(line, hashTable, default_hash_function);
#elif AVLTREE
        append(line, &root, Default_AVL_Compare);
#else
        e = append(line, e);
#endif
    }
    clock_gettime(CLOCK_REALTIME, &end);
    cpu_time1 = diff_in_second(start, end);

    /* close file as soon as possible */
    fclose(fp);

    /* the givn last name to find */
    char input[MAX_LAST_NAME_SIZE] = "zyxel";
    e = pHead;

#if defined(__GNUC__)
    __builtin___clear_cache((char*)pHead, (char*)pHead + sizeof(entry));
#endif
    /* compute the execution time */
    clock_gettime(CLOCK_REALTIME, &start);
#ifdef HASH
    findName(input, hashTable, default_hash_function);
#elif AVLTREE
    entry* ret = findName(input, root);
    assert(ret != NULL);
    printf("%s\n", ret->lastName);
#else
    findName(input, e);
#endif
    clock_gettime(CLOCK_REALTIME, &end);
    cpu_time2 = diff_in_second(start, end);

#if defined(HASH)
    FILE* output = fopen(OUT_FILE, "a");
    fprintf(output, "append() findName() %lf %lf\n", cpu_time1, cpu_time2);
    fclose(output);
#else
    FILE* output = fopen(OUT_FILE, "a");
    fprintf(output, "append() findName() %lf %lf\n", cpu_time1, cpu_time2);
    fclose(output);

    printf("execution time of append() : %lf sec\n", cpu_time1);
    printf("execution time of findName() : %lf sec\n", cpu_time2);
#endif

#ifdef MEM_POOL
    pool_free(pool);
#elif AVLTREE
    AVLTreeDestroy(&root);
    free(root);
#else
    if (pHead->pNext) {
        while (pHead->pNext) {
            entry* cur = pHead->pNext;
            free(pHead);
            pHead = cur;
        }
    }

#endif
    free(pHead);
    return 0;
}
