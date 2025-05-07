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

    TreeNode* node1 = bst_search(tree,9);
    printf("key: %d\n",node1->key);
    printf("left: %d\n",node1->left->key);
    printf("right: %d\n",node1->right->key);

    //广度搜索
    bst_levellorder(tree);
    printf("\n");
    bst_delete(tree,9);
    bst_levellorder(tree);

    //深度搜索
    // bst_inorder(tree->root);
    // printf("\n");
    // bst_preorder(tree->root);
    // printf("\n");
    // bst_backorder(tree->root);

    bst_destroy(tree->root);
    free(tree);

    return 0;
}