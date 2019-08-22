/*
* @Author: jobbofhe
* @Date:   2019-08-18 16:54:31
* @Last Modified by:   Administrator
* @Last Modified time: 2019-08-21 20:26:07
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// 定义节点
typedef int Type;

typedef struct AVLTreeNode
{
    Type key;       // 值
    int height;     // 树的高度
    struct AVLTreeNode *left;
    struct AVLTreeNode *right;
    
}Node, *AVLTree;

// 创建节点
static Node *avltree_create_node(Type key, Node *left, Node *right)
{
    Node *p = (Node *)malloc(sizeof(Node));

    if (!p)
    {
        return NULL;
    }

    p->key = key;
    p->height = 0;
    p->left = left;
    p->right = right;

    return p;
}

// 本文采用维基百科上的定义：树的高度为最大层次。
// 即空的二叉树的高度是0，非空树的高度等于它的最大层次(根的层次为1，根的子节点为第2层，依次类推)。

#define HEIGHT(p)  ((p == NULL) ? 0 : ((Node *)(p))->height)

int avltree_height(AVLTree tree)
{
    return HEIGHT(tree);
}

#define MAX(a, b) ((a) > (b) ? (a) : (b))
#define MIN(a, b) ((a) < (b) ? (a) : (b))



int main(int argc, char const *argv[])
{
    printf("test\n");

    static bool stopFlag;
    printf("%d\n", stopFlag);
    
    return 0;
}

static Node *left_left_rotation(AVLTree keyRoot)
{
    AVLTree keyTmp;

    keyTmp = keyRoot->left;
    keyRoot->left = keyTmp->right;
    keyTmp->right = keyRoot;

    keyRoot->height = MAX(HEIGHT(keyRoot->left), (keyRoot->right)) + 1;
    keyTmp->height =  MAX(HEIGHT(keyTmp->left), keyRoot->height) + 1;

    return keyTmp;
}

