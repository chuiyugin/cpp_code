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
void bst_destroy(TreeNode* root);

//基本操作
void bst_insert(BST* tree,K key);
TreeNode* bst_search(BST* tree,K key);
void bst_delete(BST* tree,K key);

//广度搜索(层次遍历)
void bst_levellorder(BST* tree);
//中序遍历
void bst_inorder(TreeNode* root);
//先序遍历
void bst_preorder(TreeNode* root);
//后序遍历
void bst_backorder(TreeNode* root);