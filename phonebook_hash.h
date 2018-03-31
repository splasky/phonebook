#ifndef _PHONEBOOK_H
#define _PHONEBOOK_H

#include "hash_function.h"
#define MAX_LAST_NAME_SIZE 16

typedef struct __INNDER_DETAILS {
    char firstName[16];
    char email[16];
    char phone[10];
    char cell[10];
    char addr1[16];
    char addr2[16];
    char city[16];
    char state[2];
    char zip[5];
} details;

typedef struct __PHONE_BOOK_ENTRY {
    char lastName[MAX_LAST_NAME_SIZE];
    details* detail;
    struct __PHONE_BOOK_ENTRY* pNext;
    struct __PHONE_BOOK_ENTRY* pLast;
} entry;

entry* findName(
    char lastName[], entry* table[], hash_function func, unsigned int hash_table_size);
void append(
    char lastName[], entry* table[], hash_function func, unsigned int hash_table_size);
void initHashTable(entry* table[], unsigned int hash_table_size);

#endif
