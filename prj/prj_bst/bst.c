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
    K cmp;//用于比较，只需要比较一次
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
    K cmp;//用于比较，只需要比较一次
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
    destroy_queue(q);
}

//中序遍历(二叉排序树)
void bst_inorder(TreeNode* root)
{
    //边界条件
    if(root == NULL)
        return;
    //递归公式
    //遍历左子树
    bst_inorder(root->left);
    //遍历根节点
    printf("%d ",root->key);
    //遍历右子树
    bst_inorder(root->right);
}

//先序遍历
void bst_preorder(TreeNode* root)
{
    //边界条件
    if(root == NULL)
        return;
    //递归公式
    //遍历根节点
    printf("%d ",root->key);
    //遍历左子树
    bst_preorder(root->left);
    //遍历右子树
    bst_preorder(root->right);
}

//后序遍历
void bst_backorder(TreeNode* root)
{
    //边界条件
    if(root == NULL)
        return;
    //递归公式
    //遍历左子树
    bst_backorder(root->left);
    //遍历右子树
    bst_backorder(root->right);
    //遍历根节点
    printf("%d ",root->key);
}

//删除节点
void bst_delete(BST* tree,K key)
{
    // 1.找到要删除的节点
    TreeNode* parent = NULL;
    TreeNode* cur = tree->root;
    K cmp;
    while(cur != NULL)
    {
        cmp = key - cur->key;
        if(cmp < 0) //key < cur->key,向左边找
        {
            parent = cur;
            cur = cur->left;
        }
        else if(cmp > 0)
        {
            parent = cur;
            cur = cur->right;
        }
        else
            break;
    }//cur == NULL || cur != NULL
    if(cur == NULL)
        return;
    // 2.删除节点
    if(cur->left && cur->right) // 度为2的情况
    {
        //退化成度为0或度为1的情况
        //先找右子树的最小节点
        TreeNode* pr_min = cur;
        TreeNode* r_min = cur->right;
        while(r_min->left != NULL)
        {
            pr_min = r_min;
            r_min = r_min->left;
        }
        //退化过程
        cur->key = r_min->key;
        cur = r_min;
        parent = pr_min;
    }
    //度为0或1的情况
    //找到唯一的孩子
    TreeNode* child = cur->left ? cur->left : cur->right;
    if(parent == NULL) // 删除的是根节点
    {
        tree->root = child;
    }
    else
    {
        //将child链接到parent正确的位置
        //必须重新比较，因为可能出现了退化
        K cmp = cur->key - parent->key;
        if(cmp<0)
        {
            parent->left = child;
        }
        else if(cmp>0)
        {
            parent->right = child;
        }
        else //注意：特例cmp==0，右子树最小节点就是右子树根节点
        {
            parent->right = child;
        }
    }
    free(cur);
}

void bst_destroy(TreeNode* root)
{
    //边界条件
    if(root == NULL)
    {
        return;
    }
    //递归公式
    //遍历左子树
    bst_destroy(root->left);
    //遍历右子树
    bst_destroy(root->right);
    //遍历根节点
    free(root);
}