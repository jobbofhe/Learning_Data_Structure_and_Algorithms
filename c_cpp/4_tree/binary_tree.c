/*
* @Author: jobbofhe
* @Date:   2019-07-29 20:08:30
* @Last Modified by:   Administrator
* @Last Modified time: 2019-08-07 20:11:18
*/


#include <stdio.h>
#include <stdlib.h>

typedef int TYPE;

// 二叉查找树的节点包含的基本信息：
// (01) key       -- 它是关键字，是用来对二叉查找树的节点进行排序的。
// (02) left       -- 它指向当前节点的左孩子。
// (03) right    -- 它指向当前节点的右孩子。
// (04) parent -- 它指向当前节点的父结点。

typedef struct BSTreeNode
{
    TYPE key;
    struct BSTreeNode *left;
    struct BSTreeNode *right;
    struct BSTreeNode *parent;
    
}Node, *BSTree;


Node *create_bstree_node(TYPE key, Node *parent, Node *left, Node *right);

Node *insert_bstree(BSTree tree, TYPE key);

// 前根序遍历
void pre_order_bstree(BSTree tree);

// 中根序遍历
void middle_order_bstree(BSTree tree);

// 后根序遍历
void behind_order_bstree(BSTree tree);

// 中根序
// 递归方式
// 在二叉树中，查找值为key的节点
Node *bstree_search_recursion(BSTree tree, TYPE key);
// 中根序
// 循环方式
// 在二叉树中，查找值为key的节点
Node *bstree_search(BSTree tree, TYPE key);

// 中根序，查找最大值
Node *bstree_search_max(Node *pnode);

// 中根序，朝赵最小值
Node *bstree_search_min(Node *pnode);

// 中根序，查找 某结点的前驱
Node *bstree_search_predecessor(Node *pnode);
// 中根序，查找 某结点的后继结点
Node *bstree_search_successor(Node *pnode);

// 内部接口
// 中根序 向树tree中插入一个结点，返回插入后的树的根节点
static Node *bstree_insert(BSTree tree, Node *newNode);

// 外部接口，在树中新建结点，并返回根节点
Node *create_bstree(BSTree tree, TYPE key);

// 删除节点
static Node *bstree_delete_node(BSTree tree, Node *dstNode);

// 打印整颗二叉树(tree)。其中，tree是二叉树节点，key是二叉树的键值，而direction表示该节点的类型：

// direction为 0，表示该节点是根节点;
// direction为-1，表示该节点是它的父结点的左孩子;
// direction为 1，表示该节点是它的父结点的右孩子。
void printf_bstree(BSTree tree, TYPE key, int direction);

void destroy_bstree(BSTree tree);


Node *create_bstree_node(TYPE key, Node *parent, Node *left, Node *right)
{
    Node *p = (Node*)malloc(sizeof(Node));

    if (NULL == p)
    {
        printf("Faild to malloc!\n");
        return NULL;
    }

    p->key = key;
    p->parent = parent;
    p->left = left;
    p->right = right;

    return p;
}

Node *insert_bstree(BSTree tree, TYPE key)
{
    Node * pnode = create_bstree_node(key, NULL, NULL, NULL);

    if (NULL == pnode)
    {
        printf("Faile create bstree node!\n");
        return tree;
    }

    return tree;    
}

// 前根序遍历
void pre_order_bstree(BSTree tree)
{
    if (NULL == tree)
    {
        return ;
    }

    printf("%d ", tree->key);
    pre_order_bstree(tree->left);
    pre_order_bstree(tree->right);
}

// 中根序遍历
void middle_order_bstree(BSTree tree)
{
    if (NULL == tree)
    {
        return ;
    }

    middle_order_bstree(tree->left);
    printf("%d ", tree->key);
    middle_order_bstree(tree->right);
}

// 后根序遍历
void behind_order_bstree(BSTree tree)
{
    if (NULL == tree)
    {
        return ;
    }

    behind_order_bstree(tree->left);
    behind_order_bstree(tree->right);
    printf("%d ", tree->key);
}

// 中根序
// 递归方式
// 在二叉树中，查找值为key的节点
Node *bstree_search_recursion(BSTree tree, TYPE key)
{
    if (tree == NULL || tree->key == key)
    {
        return tree;
    }

    if (key < tree->key)
    {
        return bstree_search(tree->left, key);
    }
    else
    {
        return bstree_search(tree->right, key);
    }
}

// 中根序
// 循环方式
// 在二叉树中，查找值为key的节点
Node *bstree_search(BSTree tree, TYPE key)
{
    if (NULL == tree)
    {
        return tree;
    }
    while(NULL != tree && (tree->key != key))
    {
        if (key < tree->key)
        {
            tree = tree->left;
        }
        else
        {
            tree = tree->right;
        }
    }

    return tree;
}

// 中根序，查找最大值
Node *bstree_search_max(Node *pnode)
{
    if (NULL == pnode)
    {
        return pnode;
    }

    while(pnode->right != NULL) 
    {
        pnode = pnode->right;
    }

    return pnode;
}

// 中根序，朝赵最小值
Node *bstree_search_min(Node *pnode)
{
    if (NULL == pnode)
    {
        return pnode;
    }

    while(pnode->left != NULL) 
    {
        pnode = pnode->left;
    }

    return pnode;
}

// 中根序，查找 某结点的前驱
Node *bstree_search_predecessor(Node *pnode)
{
    
    if (NULL == pnode)
    {
        return pnode;
    }

    // 如果 pnode 存在左孩子，则它的前驱是，以它的左孩子为根节点的子树的最大结点
    while(NULL != pnode->left) 
    {
        return bstree_search_max(pnode->left);
    }

    // 如果 pnode 没有左孩子，则有以下两种可能
    // 1) pnode 是一个右孩子，那么他的前驱就是 它的父节点
    // 2) pnode 是一个左孩子，那么 查找 pnode 的最低的 父节点，并且该父节点要具有右孩子， 找到的这个最低的父节点 就是 x的前驱节点
    Node *tmp = pnode->parent;
    while(NULL != tmp && (pnode == tmp->left)) 
    {
        pnode = tmp;
        tmp = tmp->parent;
    }

    return tmp;
}

// 中根序，查找 某结点的后继结点
Node *bstree_search_successor(Node *pnode)
{
    
    if (NULL == pnode)
    {
        return pnode;
    }

    // 如果 pnode 存在右孩子，则它的后继就是他的右孩子
    while(NULL != pnode->left) 
    {
        return bstree_search_max(pnode->left);
    }

    // 如果 pnode 没有右孩子，则有以下两种可能
    // 1) pnode 是一个左孩子，那么他后继就是 它的父节点
    // 2) pnode 是一个右孩子，那么 查找 pnode 的最低的 父节点，并且该父节点要具有左孩子， 找到的这个最低的父节点 就是 x的后继节点
    Node *tmp = pnode->parent;
    while(NULL != tmp && (pnode == tmp->left)) 
    {
        pnode = tmp;
        tmp = tmp->parent;
    }

    return tmp;
}

// 内部接口
// 中根序 向树tree中插入一个结点，返回插入后的树的根节点
static Node *bstree_insert(BSTree tree, Node *newNode)
{
    if (newNode == NULL)
    {
        return tree;
    }

    Node *pTree = tree;
    Node *pTmp = NULL;

    // 找到要插入的位置
    while(NULL != pTree) 
    {
        pTmp = pTree;
        // 新节点小于根节点
        if (newNode->key < pTree->key)
        {
            pTree = pTree->left;
        }
        else if(newNode->key > pTree->key) // 新节点大于根节点
        {
            pTree = pTree->right;
        }
        else // 新节点等于根节点
        {
            free(newNode);

            return tree;
        }
    }
    newNode->parent = pTmp;

    // 如果没有找到要插入的位置，即tree为空
    if(pTmp == NULL)
    {
        tree = newNode;
    }
    else if (newNode->key < pTmp->key)
    {
        pTmp->left = newNode;
    }
    else
    {
        pTmp->right = newNode;
    }

    return tree;
}

// 外部接口，在树中新建结点，并返回根节点
Node *create_bstree(BSTree tree, TYPE key)
{
    Node *newNode;

    // 创建新结点
    newNode = create_bstree_node(key, NULL,  NULL, NULL);
    if (NULL == newNode)
    {
        return tree;
    }

    return bstree_insert(tree, newNode);
}

// 删除节点
static Node *bstree_delete_node(BSTree tree, Node *dstNode)
{
    Node *x = NULL;
    Node *y = NULL;

    // 根据要删除的结点的类型，确定要删除的节点或者他的后继
    if (dstNode->left == NULL || dstNode->right == NULL)
    {
        y = dstNode;
    }
    else // 左右孩子都不为空
    {
        // 查找要删除的节点的 后继
        y = bstree_search_successor(dstNode);
    }

    if (y->left != NULL)
    {
        x = y->left;
    }
    else
    {
        x = y->right;
    }

    if (x != NULL)
    {
        x->parent = y->parent;
    }

    if (y->parent == NULL)
    {
        tree = x;
    }
    else if (y == y->parent->left)
    {
        y->parent->left = x;
    }
    else
    {
        y->parent->right = x;
    }

    if (y != dstNode)
    {
        dstNode->key = y->key;
    }

    if (y != NULL)
    {
        free(y);
    }

    return tree;
}

// 删除值为key的节点
Node* bstree_delete_key(BSTree tree, TYPE key)
{
    Node *z, *node; 

    if ((z = bstree_search(tree, key)) != NULL)
        tree = bstree_delete_node(tree, z);

    return tree;
}

// 打印整颗二叉树(tree)。其中，tree是二叉树节点，key是二叉树的键值，而direction表示该节点的类型：

// direction为 0，表示该节点是根节点;
// direction为-1，表示该节点是它的父结点的左孩子;
// direction为 1，表示该节点是它的父结点的右孩子。
void printf_bstree(BSTree tree, TYPE key, int direction)
{
    if (NULL == tree)
    {
        return;
    }

    // 根节点
    if (0 == direction) 
    {
        printf("%3d is root.\n", tree->key);
    }
    else
    {
        printf("%3d is %3d's %6s child.\n", tree->key, key, direction == 1?"right":"left");
    }

    printf_bstree(tree->left, tree->key, -1);
    printf_bstree(tree->right, tree->key, 1);
}

void destroy_bstree(BSTree tree)
{
    if (tree == NULL)
    {
        return;
    }

    if (tree->left != NULL)
    {
        destroy_bstree(tree->left);
    }
    if (tree->right != NULL)
    {
        destroy_bstree(tree->right);
    }

    free(tree);
}


static int arr[] = {3, 54, 6, 7, 43, 9, 59, 55, 0, 2};
int main(int argc, char const *argv[])
{
    Node *root;

    int i = 0;
    printf("--> 新建结点: ");
    for (i=0; i < 10; ++i)
    {
        printf("%d ", arr[i]);
        root = create_bstree(root, arr[i]);
    }

    printf("\n--> 前序遍历: ");
    pre_order_bstree(root);

    printf("\n--> 中序遍历: ");
    middle_order_bstree(root);

    printf("\n--> 后序遍历: ");
    behind_order_bstree(root);

    printf("\n--> 最大值: ");
    Node *max = bstree_search_max(root);
    printf(" %d", max->key);

    printf("\n--> 最小值: ");
    Node *min = bstree_search_min(root);
    printf(" %d", min->key);

    printf("\n--> 查找55节点: ");
    Node *node = bstree_search(root, 55);
    printf(" %d", node->key);

    printf("\n--> 打印二叉树：\n");
    printf_bstree(root, root->key, 0);

    bstree_delete_key(root, 55);

    printf("\n--> 最大值: ");
    max = bstree_search_max(root);
    printf(" %d", max->key);

    printf("\n--> 前序遍历: ");
    pre_order_bstree(root);
    printf("\n");

    destroy_bstree(root);

    return 0;
}