#include <stdlib.h>
#include <string.h>
#include <strings.h>

#include "phonebook_avltree.h"

entry* findName(char lastName[], AVLTreeNode* root)
{
    entry* ret = AVLTreeFind(root, lastName);
    return ret;
}

void append(char lastName[], AVLTreeNode** root, AVLTree_compare compare)
{
    entry* e = (entry*)malloc(sizeof(entry));
    strcpy(e->lastName, lastName);
    AVLTreeInsert(root, e->lastName, e, compare);
}
