#ifndef AVLTREE_H_WYM1ZCXV
#define AVLTREE_H_WYM1ZCXV

#define LEFT (0)
#define RIGHT (1)
#define NUM_OF_CHILDREN (2)

/* Less than:-1
 * equal to :0
 * more than:1
 */
typedef int (*AVLTree_compare)(const void* a, const void* b);

typedef struct _AVLTREENODE {
    unsigned int height;
    void* key;
    void* data;
    AVLTree_compare compare;
    struct _AVLTREENODE* child[NUM_OF_CHILDREN];
} AVLTreeNode;

void AVLTreeInsert(AVLTreeNode** root, void* key, void* data, AVLTree_compare);
void* AVLTreeFind(AVLTreeNode* root, void* key);
void AVLTreeDestroy(AVLTreeNode** root);

#endif /* end of include guard: AVLTREE_H_WYM1ZCXV */
