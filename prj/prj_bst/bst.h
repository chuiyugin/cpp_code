#include <stdio.h>
#include <stdlib.h>

typedef int K;

typedef struct tree_node{
    K key;
    struct tree_node* left;
    struct tree_node* right;
} TreeNode;

typedef struct {
    TreeNode* root;
} BST;

//API
BST* bst_create();
void bst_destroy(BST* tree);

//基本操作
void bst_insert(BST* tree,K key);
TreeNode* bst_search(BST* tree,K key);
void bst_delete(BST* tree,K key);

//遍历
void bst_levellorder(BST* tree);
