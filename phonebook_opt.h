#ifndef _PHONEBOOK_H
#define _PHONEBOOK_H

#define MAX_LAST_NAME_SIZE 16

extern unsigned int HASH_TABLE_SIZE;
#define OPT 1
typedef struct __PHONE_BOOK_ENTRY {
    char lastName[MAX_LAST_NAME_SIZE];
    char firstName[16];
    char email[16];
    char phone[10];
    char cell[10];
    char addr1[16];
    char addr2[16];
    char city[16];
    char state[2];
    char zip[5];
    struct __PHONE_BOOK_ENTRY* pNext;
} entry;

typedef unsigned int (*hash_function)(const char* str, unsigned int length);

entry* findName(char lastName[], entry* table[], hash_function func);
void append(char lastName[], entry* table[], hash_function func);
unsigned hash(char* name, hash_function func);
void initHashTable(entry* table[]);

#endif
