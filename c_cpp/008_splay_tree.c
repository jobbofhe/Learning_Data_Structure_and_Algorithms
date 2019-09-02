/*
* @Author: jobbofhe
* @Date:   2019-08-29 10:03:17
* @Last Modified by:   Administrator
* @Last Modified time: 2019-09-02 20:22:53
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
 * 插入伸展树一个节点，返回根节点
 */
Node *splaytree_insert(SplayTree tree, Type key);

/**
 * 删除伸展树中值为key的节点，返回根节点
 */
Node *splaytree_delete(SplayTree tree, Type key);

/**
 * 打印伸展树的详细信息
 */
void splaytree_print(SplayTree tree);

/**
 * 销毁伸展树
 */
void splaytree_destroy(SplayTree tree);

/**
 * 创建节点
 */
static Node *create_node(Type key, Node *left, Node *right);

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
// 
Node *splaytree_splay(SplayTree tree, Type key)
{

}

Node *splaytree_insert(SplayTree tree, Type key)
{

}


Node *splaytree_delete(SplayTree tree, Type key)
{

}

void splaytree_print(SplayTree tree)
{

}

void splaytree_destroy(SplayTree tree)
{

}


int main(int argc, char const *argv[])
{
    
    return 0;
}