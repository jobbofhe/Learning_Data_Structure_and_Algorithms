/*
* @Author: jobbofhe
* @Date:   2019-09-11 21:01:00
* @Last Modified by:   Administrator
* @Last Modified time: 2019-09-16 20:16:25
*/

/**
 * 数据结构定义
 */

#include <stdio.h>
#include <stdlib.h>

#define RED     (0)
#define BLACK   (1)

#define RB_PARENT(r)            ((r)->parent)
#define RB_COLOR(r)             ((r)->color)
#define RB_IS_RED(r)            ((r)->color == RED)
#define RB_IS_BLACK(r)          ((r)->color == BLACK)
#define RB_SET_RED(r)           do { (r)->color = RED; } while (0)
#define RB_SET_BLACK(r)         do { (r)->color = BLACK; } while (0)
#define RB_SET_PARENT(r, p)     do { (r)->parent = p; } while (0)
#define RB_SET_COLOR(r, c)      do { (r)->color = c; } while (0)


typedef int Type;

typedef struct RBTreeNode
{
    int color;
    Type key;
    struct RBTreeNode *left;
    struct RBTreeNode *right;
    struct RBTreeNode *parent;

}Node, *RBTree;

// 红黑树的根
typedef struct RB_ROOT
{
    Node *node;

}RBRoot;


// 函数声明


/**
 * 创建红黑树的根
 */
RBRoot *create_rbtree();

/**
 * 前根序遍历红黑树
 */
void rbtree_preorder(RBTree tree);

/**
 * 中根序遍历红黑树
 */
void rbtree_inorder(RBTree tree);

/**
 * 后根序遍历
 */
void rbtree_behindorder(RBTree tree);

/**
 * 【递归实现】
 *  查找树中值为 key的节点
 * @param  tree [树]
 * @param  key  [值]
 * @return      [返回找到的节点]
 */
static Node *search(RBTree tree, Type key);

/**
 * 查找树中的key值的点
 * @return      [找到返回 0，  未找到返回 -1]
 */
int rbtree_search(RBRoot *root, Type key);

// 函数定义


int rbtree_search(RBRoot *root, Type key)
{
    if (root)
    {
        return search(root->node, key) ? 0:-1;
    }
}

static Node *search(RBTree tree, Type key)
{
    if (tree == NULL || tree->key == key)
    {
        return tree;
    }

    if (key < tree->key)
    {
        return search(tree->left, key);
    }
    else
    {
        return search(tree->right, key);
    }
}

void rbtree_behindorder(RBTree tree)
{
    if (tree == NULL)
    {
        printf("Red tree is empty!\n");
        return ;
    }

    rbtree_preorder(tree->left);
    rbtree_preorder(tree->right);
    printf("%d ", tree->key);
    
}

void rbtree_inorder(RBTree tree)
{
    if (tree == NULL)
    {
        printf("Red tree is empty!\n");
        return ;
    }

    rbtree_preorder(tree->left);
    printf("%d ", tree->key);
    rbtree_preorder(tree->right);
}

void rbtree_preorder(RBTree tree)
{
    if (tree == NULL)
    {
        printf("Red tree is empty!\n");
        return ;
    }

    printf("%d ", tree->key);
    rbtree_preorder(tree->left);
    rbtree_preorder(tree->right);
}

RBRoot *create_rbtree()
{
    RBRoot *root = (RBRoot *)malloc(sizeof(RBRoot));
    if (!root)
    {
        printf("Failed to malloc memery.\n");
        
        return root;
    }
    root->node = NULL;

    return root;
}


/**
 * 测试
 */

int main(int argc, char const *argv[])
{
    /* code */
    return 0;
}