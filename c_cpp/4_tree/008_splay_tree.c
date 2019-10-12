/*
* @Author: jobbofhe
* @Date:   2019-08-29 10:03:17
* @Last Modified by:   Administrator
* @Last Modified time: 2019-09-06 21:03:01
*/

/**
 * 伸展树(归属二叉查找树)
 * 
 * 复杂度：
 *     O(log n)
 * 特点：
 *     1. 任意节点node， node->left <= node->key, node->right >= node->key
 *     2. 当某个节点被访问时，伸展树会通过旋转使该节点成为树根。
 * 
 * 适用场景：
 *     适合用于插入删除次数比较少，但查找多的情况。
 */
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// 节点定义
typedef int Type;

typedef struct SplayTreeNode
{
    Type key;
    struct SplayTreeNode *left;
    struct SplayTreeNode *right;

}Node, *SplayTree;

/**
 * 前根序遍历
 * @param tree [根节点]
 */
void pre_order_bstree(SplayTree tree);

/**
 * 中根序遍历
 * @param tree [根节点]
 */
void middle_order_bstree(SplayTree tree);

/**
 * 后根序遍历
 * @param tree [根节点]
 */
void behind_order_bstree(SplayTree tree);

/**
 * 递归实现
 * 从书中查找节点为 key的值
 * @param  tree [伸展树根节点]
 * @param  key  [关键值]
 * @return      [返回找到的节点]
 */
Node *splaytree_search(SplayTree tree, Type key);

/**
 * 循环实现查找
 * @param  tree [伸展树根节点]
 * @param  key  [关键值]
 * @return      [返回找到的节点]
 */
Node *splaytree_search_loop(SplayTree tree, Type key);

/**
 * 查找伸展树中最大的节点，并返回该节点
 */
Node *splaytree_search_max(SplayTree tree);

/**
 * 查找伸展树中最小的节点，并返回该节点
 */
Node *splaytree_search_min(SplayTree tree);

/**
 * 对伸展树执行旋转，将key对应的节点旋转为 根节点，返回根节点
 */
Node *splaytree_splay(SplayTree tree, Type key);

/**
 * 根据 节点值，创建节点，插入伸展树, 并且旋转
 */
Node *splaytree_insert(SplayTree tree, Type key);

/**
 * 将一个已经创建好的节点插入伸展树， 不旋转，返回根节点
 */
static Node *splaytree_insert_node(SplayTree tree, Node *node);

/**
 * 删除伸展树中值为key的节点，返回根节点
 */
Node *splaytree_delete(SplayTree tree, Type key);


/**
 * 打印伸展树的详细信息
 * @param direction [direction  --  0，表示该节点是根节点;
                 -1，表示该节点是它的父结点的左孩子;
                  1，表示该节点是它的父结点的右孩子]
 */
void splaytree_print(SplayTree tree, Type key, int direction);

/**
 * 销毁伸展树
 */
void splaytree_destroy(SplayTree tree);

/**
 * 创建节点
 */
// static Node *create_node(Type key, Node *left, Node *right);

static Node *splaytree_create_node(Type key, Node *left, Node *right);

// *******************************************************************************************


void pre_order_bstree(SplayTree tree)
{
    if(NULL == tree)
    {
        return ;
    }

    printf("%d ",  tree->key);
    pre_order_bstree(tree->left);
    pre_order_bstree(tree->right);
}

void middle_order_bstree(SplayTree tree)
{
    if(NULL == tree)
    {
        return ;
    }

    middle_order_bstree(tree->left);
    printf("%d ",  tree->key);
    middle_order_bstree(tree->right);
}

void behind_order_bstree(SplayTree tree)
{
    if(NULL == tree)
    {
        return ;
    }

    behind_order_bstree(tree->left);
    behind_order_bstree(tree->right);
    printf("%d ", tree->key);
}

Node *splaytree_search(SplayTree tree, Type key)
{
    if (NULL == tree || tree->key == key)
    {
        return tree;
    }

    if (key < tree->key)
    {
        return splaytree_search(tree->left, key);
    }
    else
    {
        return splaytree_search(tree->right, key);
    }
}

Node *splaytree_search_loop(SplayTree tree, Type key)
{   
    Node *p = tree;

    while(p != NULL && p->key != key) 
    {
        if (key < p->key)
        {
            p = p->left;
        }
        else
        {
            p = p->right;
        }
    }

    return p;
}

Node *splaytree_search_max(SplayTree tree)
{
    if (NULL == tree)
    {
        return NULL;
    }

    Node *p = tree;
    while(p->right != NULL) 
    {
        p = p->right;
    }

    return p;
}


Node *splaytree_search_min(SplayTree tree)
{
    if (NULL == tree)
    {
        return NULL;
    }

    Node *p = tree;
    while(p->left != NULL) 
    {
        p = p->left;
    }

    return p;
}

// 最核心的代码
// /* 
// 108  * 旋转key对应的节点为根节点，并返回根节点。
// 109  *
// 110  * 注意：
// 111  *   (a)：伸展树中存在"键值为key的节点"。
// 112  *          将"键值为key的节点"旋转为根节点。
// 113  *   (b)：伸展树中不存在"键值为key的节点"，并且key < tree->key。
// 114  *      b-1 "键值为key的节点"的前驱节点存在的话，将"键值为key的节点"的前驱节点旋转为根节点。
// 115  *      b-2 "键值为key的节点"的前驱节点存在的话，则意味着，key比树中任何键值都小，那么此时，将最小节点旋转为根节点。
// 116  *   (c)：伸展树中不存在"键值为key的节点"，并且key > tree->key。
// 117  *      c-1 "键值为key的节点"的后继节点存在的话，将"键值为key的节点"的后继节点旋转为根节点。
// 118  *      c-2 "键值为key的节点"的后继节点不存在的话，则意味着，key比树中任何键值都大，那么此时，将最大节点旋转为根节点。
// 119  */
// 
Node *splaytree_splay(SplayTree tree, Type key)
{
    if (tree == NULL)
    {
        return tree;
    }

    Node tmp, *l, *r, *c;

    tmp.left = tmp.right = NULL;
    l = r = &tmp;

    while(true) 
    {
        // 查找的节点在根节点的左子树上
        if (key < tree->key)
        {
            // 如果根节点的左子树为空，也就是说，要查找的节点不存在
            if (tree->left == NULL)
            {
                break;
            }
            // 如果要查找的节点小于根节点的左孩子的值，那么要进行右旋转
            if (key < tree->left->key)
            {   
                c = tree->left;
                tree->left = c->right;
                c->right = tree;
                tree = c;
                if (tree->left == NULL)
                {
                    break;
                }
            }
            r->left = tree;
            r = tree;
            tree = tree->left;
        }
        else if (key > tree->key)
        {
            if (tree->right == NULL)
            {
                break;
            }
            if (key > tree->right->key)
            {
                c = tree->right;
                tree->right = c->left;
                c->left = tree;
                tree = c;
                if (tree->right == NULL)
                {
                    break;
                }
            }
            l->right = tree;
            l = tree;
            tree = tree->right;
        }
        else
        {
            break;
        }
    }

    l->right = tree->left;
    r->left = tree->right;
    tree->left = tmp.right;
    tree->right = tmp.left;

    return tree;
}

static Node *splaytree_insert_node(SplayTree tree, Node *node)
{
    Node *p = tree;
    Node *tmp = NULL;

    // 查找插入的位置
    while(p != NULL) 
    {
        tmp = p;
        if (node->key < p->key)
        {
            p = p->left;
        }
        else if (node->key > p->key)
        {
            p = p->right;
        }
        else
        {
            printf("插入的值[%d]已存在树中。\n", node->key);
            if (node)
            {
                free(node);
            }
            
            return tree;
        }
    }

    if (tmp == NULL)
    {
        tree = node;
    }
    else if (node->key < tmp->key)
    {
        tmp->left = node;
    }
    else
    {
        tmp->right = node;
    }

    return tree;
}


Node *splaytree_insert(SplayTree tree, Type key)
{
    Node *node = splaytree_create_node(key, NULL, NULL);

    if (NULL == node)
    {
        printf("Faild to create node!\n");
        return tree;
    }

    tree = splaytree_insert_node(tree, node);

    // 将新插入的节点旋转为根节点
    tree = splaytree_splay(tree, key);

    return tree;
}

/*
    删除结点(key为节点的键值)，并返回根节点。
 */
Node *splaytree_delete(SplayTree tree, Type key)
{
    if (NULL == tree)
    {
        printf("Tree is empty!\n");
        return NULL;
    }

    Node *p = NULL;

    Node *node = splaytree_search(tree, key);
    if (NULL == node)
    {
        printf("Can't find node [%d]!\n", key);
        return tree;
    }

    // 存在节点  key, 将该节点旋转为 根节点
    tree = splaytree_splay(tree, key);

    // 此时要删除根节点，所以要将跟节点的 做孩子，旋转为根节点，然后释放根节点
    if (tree->left != NULL)
    {   
        p = splaytree_splay(tree->left, key);
        p->right = tree->right;
    }
    else
    {
        // 根节点不存在左子树，
        p = tree->right;
    }

    free(tree);

    return p;
}

void splaytree_print(SplayTree tree, Type key, int direction)
{
    if (tree != NULL)
    {
        if (direction == 0)
        {
            printf("%3d is root\n", tree->key);
        }
        else
        {
            printf("%3d is %3d's %8s child\n", tree->key, key, direction == 1? "right":"left");
        }
        splaytree_print(tree->left, tree->key, -1);
        splaytree_print(tree->right, tree->key, 1);
    }
}

void splaytree_destroy(SplayTree tree)
{
    if (NULL == tree)
    {
        return;
    }

    if (tree->left != NULL)
    {
        splaytree_destroy(tree->left);
    }
    if (tree->right != NULL)
    {
        splaytree_destroy(tree->right);
    }

    free(tree);
}

static Node *splaytree_create_node(Type key, Node *left, Node *right)
{
    Node *p = (Node*)malloc(sizeof(Node));

    if (NULL == p)
    {
        printf("Faild to malloc!\n");
        return NULL;
    }

    p->key = key;
    p->left = left;
    p->right = right;

    return p;
}

static int arr[]= {10,50,40,30,20,60};
#define SIZE(a) ( (sizeof(a)) / (sizeof(a[0])) )

int main(int argc, char const *argv[])
{
    int i, ilen;
    SplayTree root=NULL;

    printf("---->  依次添加: ");
    ilen = SIZE(arr);
    for(i=0; i<ilen; i++)
    {
        printf("%d ", arr[i]);
        root = splaytree_insert(root, arr[i]);
    }

    printf("\n----> 前序遍历: ");
    pre_order_bstree(root);

    printf("\n----> 中序遍历: ");
    middle_order_bstree(root);

    printf("\n----> 后序遍历: ");
    behind_order_bstree(root);
    printf("\n");

    printf("---->  最小值: %d\n", splaytree_search_min(root)->key);
    printf("---->  最大值: %d\n", splaytree_search_max(root)->key);
    printf("---->  树的详细信息: \n");
    splaytree_print(root, root->key, 0);

    i = 10;
    printf("\n== 旋转节点(%d)为根节点\n", i);
    printf("---->  树的详细信息: \n");
    root = splaytree_splay(root, i);
    splaytree_print(root, root->key, 0);

    // 销毁伸展树
    splaytree_destroy(root);

    
    return 0;
}