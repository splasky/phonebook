#include "avltree.h"
#include <assert.h>
#include <stdlib.h>

static AVLTreeNode* Create_AVLTreeNode(void* key, void* data, AVLTree_compare compare)
{
    AVLTreeNode* node = malloc(sizeof(AVLTreeNode));
    node->compare = compare;
    node->data = data;
    node->height = 0;
    node->key = key;
    node->child[LEFT] = node->child[RIGHT] = 0;
    return node;
}

static unsigned int AVLTree_Height(AVLTreeNode* root)
{
    if (root == 0) {
        return 0;
    } else {
        return root->height;
    }
}

static unsigned int AVLTree_ComputeHeight(AVLTreeNode* root)
{

    if (root == 0) {
        return 0;
    } else {
        int maxChildHeight = 0;
        int childHeight = 0;
        for (int i = 0; i < NUM_OF_CHILDREN; ++i) {
            childHeight = AVLTree_Height(root->child[i]);
            if (childHeight > maxChildHeight) {
                maxChildHeight = childHeight;
            }
        }

        return maxChildHeight + 1;
    }
}

static void AVLTree_AggregateFix(AVLTreeNode* root)
{
    if (root) {
        root->height = AVLTree_ComputeHeight(root);
    }
}

static void AVLTree_Rotate(AVLTreeNode** root, int direction)
{
    AVLTreeNode* y;
    AVLTreeNode* x;
    AVLTreeNode* b;

    y = *root;
    x = y->child[direction];
    b = x->child[!direction];

    *root = x;
    x->child[!direction] = y;
    y->child[direction] = b;
    AVLTree_AggregateFix(y);
    AVLTree_AggregateFix(x);
}

static void AVLTree_Reblance(AVLTreeNode** root)
{
    if (*root) {
        for (int direction = 0; direction < NUM_OF_CHILDREN; direction++) {
            if (AVLTree_Height((*root)->child[direction])
                    >= (AVLTree_Height((*root)->child[!direction]) + 2)) {

                if (AVLTree_Height((*root)->child[direction]->child[!direction])
                        > AVLTree_Height(((*root)->child[direction]->child[direction]))) {
                    AVLTree_Rotate(&(*root)->child[direction], !direction);
                }
                AVLTree_Rotate(root, direction);
                break;
            }
        }
    }
}

void AVLTreeInsert(AVLTreeNode** root, void* key, void* data, AVLTree_compare compare)
{
    if (*root == 0) {
        AVLTreeNode* e = Create_AVLTreeNode(key, data, compare);
        *root = e;
    } else if ((*root)->compare(key, (*root)->key) == 0) {
        /* Element exists,do nothing */
        return;
    } else {
        AVLTreeInsert(
            &(*root)->child[(*root)->compare((*root)->key, key) < 0], key, data, compare);
    }

    AVLTree_AggregateFix(*root);
    AVLTree_Reblance(root);
}

void AVLTreeDestroy(AVLTreeNode** root)
{
    if (*root) {
        for (int i = 0; i < NUM_OF_CHILDREN; ++i) {
            AVLTreeDestroy(&(*root)->child[i]);
        }
        free(*root);
        *root = NULL;
    }
}

void* AVLTreeFind(AVLTreeNode* root, void* key)
{

    if (root == 0) {
        return NULL;
    } else if (root->compare(root->key, key) == 0) {
        return root->data;
    }
    return AVLTreeFind(root->child[root->compare(root->key, key) < 0], key);
}
