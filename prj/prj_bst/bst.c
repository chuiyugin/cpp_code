#include "bst.h"
#include "queue.h"

//创建一颗空树
BST* bst_create()
{
    BST* root = calloc(1,sizeof(BST));
    if(root == NULL)
    {
        printf("calloc failed in bst_create!");
        exit(1);
    }
    return root;
}

//添加一个结点
//1、如果key存在则什么也不做
//2、如果key不存在，则添加一个结点
void bst_insert(BST* tree,K key)
{
    TreeNode* parent = NULL;
    TreeNode* cur = tree->root;
    int cmp;//用于比较，只需要比较一次
    while(cur!=NULL)
    {
        //比较
        cmp = key - cur->key;
        if(cmp < 0) //key < cur->key
        {
            parent = cur;
            cur = cur->left;
        }
        else if(cmp > 0) //key > cur->key
        {
            parent = cur;
            cur = cur->right;
        }
        else //key == cur->key，什么也不做
            return;
    }//此时cur == NULL
    //创建树结点
    TreeNode* new_node = calloc(1,sizeof(TreeNode));
    if(new_node == NULL)
    {
        printf("calloc failed in bst_insert!");
        exit(1);
    }
    //初始化树节点
    new_node->key = key;
    //链接到树中
    if(parent == NULL)
        tree->root = new_node;
    else if(cmp < 0) //在左边插入
        parent->left = new_node;
    else //在右边插入
    parent->right = new_node;
}

//查找一个结点
TreeNode* bst_search(BST* tree,K key)
{
    TreeNode* cur = tree->root;
    int cmp;//用于比较，只需要比较一次
    while(cur != NULL)
    {
        //比较
        cmp = key - cur->key;
        if(cmp < 0) //key < cur->key
        {
            cur = cur->left;
        }
        else if(cmp > 0) //key > cur->key
        {
            cur = cur->right;
        }
        else //key == cur->key
            return cur;
    }
    return NULL;
}

//层次遍历BST，广度优先搜索
void bst_levellorder(BST* tree)
{
    LinkedListQueue* q = create_queue(); 
    //将根节点入队列
    enqueue(q,tree->root);
    //判断队列是否为空
    while(!is_empty(q))
    {
        int level_size = q->size;
        for(int i=0;i<level_size;i++)
        {
            //出队列，遍历这个节点
            TreeNode* node = dequeue(q);
            printf("%d ",node->key);
            //判断是否有左孩子
            if(node->left)
            {
                enqueue(q,node->left);
            }
            //判断是否有右孩子
            if(node->right)
            {
                enqueue(q,node->right);
            }
        }
        printf("\n");
    }//队列为空了
}