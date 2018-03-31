#ifndef _PHONEBOOK_H
#define _PHONEBOOK_H

#include "avltree.h"
#include "hash_function.h"

#define OPT 1
#define MAX_LAST_NAME_SIZE 16
#define MEM_POOL_SIZE 100000000

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
} entry;

entry* findName(char lastName[], AVLTreeNode* table[], hash_function default_hash,
                unsigned int hash_table_size);
void append(char lastName[], AVLTreeNode* table[], hash_function default_hash,
            unsigned int hash_table_size);
void initBigTable(AVLTreeNode* table[], unsigned int hash_table_size);

#endif
