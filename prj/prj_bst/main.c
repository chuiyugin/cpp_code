#include "bst.h"

int main(void)
{
    BST* tree = bst_create();
    bst_insert(tree,9);
    bst_insert(tree,42);
    bst_insert(tree,13);
    bst_insert(tree,5);
    bst_insert(tree,57);
    bst_insert(tree,3);

    TreeNode* node1 = bst_search(tree,42);
    printf("key: %d\n",node1->key);
    printf("left: %d\n",node1->left->key);
    printf("right: %d\n",node1->right->key);

    bst_levellorder(tree);

    return 0;
}