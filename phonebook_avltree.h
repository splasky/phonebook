#ifndef _PHONEBOOK_H
#define _PHONEBOOK_H
#include "avltree.h"

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
} entry;

entry* findName(char lastName[], AVLTreeNode* root);
void append(char lastName[], AVLTreeNode** root, AVLTree_compare compare);

#endif
