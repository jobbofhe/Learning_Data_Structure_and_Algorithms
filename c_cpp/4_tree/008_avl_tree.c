/*
* @Author: jobbofhe
* @Date:   2019-08-18 16:54:31
* @Last Modified by:   Administrator
* @Last Modified time: 2019-08-26 20:13:21
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


// 本文采用维基百科上的定义：树的高度为最大层次。
// 即空的二叉树的高度是0，非空树的高度等于它的最大层次(根的层次为1，根的子节点为第2层，依次类推)。

#define HEIGHT(p)  ((p == NULL) ? 0 : ((Node *)(p))->height)

#define MAX(a, b) ((a) > (b) ? (a) : (b))
#define MIN(a, b) ((a) < (b) ? (a) : (b))


int avltree_height(AVLTree tree);

// 创建节点
static Node *avltree_create_node(Type key, Node *left, Node *right);

static Node *left_left_rotation(AVLTree keyRoot);

static Node *right_right_rotation(AVLTree keyRoot);

/**
 * LR 旋转： 要恢复，先右单旋，后左单旋
 */
static Node *left_right_rotation(AVLTree keyRoot);

static Node *right_left_rotation(AVLTree keyRoot);
/**
 * 将结点插入AVL树，返回根节点
 */
Node *avltree_insert_node(AVLTree tree, Type key);

/**
 * 递归实现
 * 查找书中值为 key的节点
 * @return      [返回找到的节点]
 */
Node *avltree_search(AVLTree tree, Type key);

/**
 * 循环实现
 * 查找书中值为 key的节点
 * @return      [返回找到的节点]
 */
Node *loop_avltree_search(AVLTree tree, Type key);

/**
 * 获取树中最大的节点
 * 最右边的节点最大
 * @param  tree [description]
 * @return      [description]
 */
Node *avltree_max_node(AVLTree tree);  

/**
 * 获取书中最小的节点
 * 最左边的节点最小
 * @param  tree [description]
 * @return      [description]
 */
Node *avltree_min_node(AVLTree tree);

/**
 * 删除节点
 * @param  tree [树根节点]
 * @param  node [被删除的节点]
 * @return      [返回根节点]
 */
Node *avltree_delete_node(AVLTree tree, Node *node);

/**
 * 根据key 值阐述树中的节点
 * @return      [返回根节点]
 */
Node *avltree_delete(AVLTree tree, Type key);

/**
 * 销毁树
 * @param tree [description]
 */
void avltree_destroy(AVLTree tree);

/**
 * 打印树
 * @param tree      [节点]
 * @param key       [key]
 * @param direction [方向 0：根节点， -1： 左孩子， 1：右孩子]
 */
void avltree_print(AVLTree tree, Type key, int direction);
// 前根序遍历
void pre_order_bstree(AVLTree tree);
// 中根序遍历
void middle_order_bstree(AVLTree tree);

// 后根序遍历
void behind_order_bstree(AVLTree tree);




int avltree_height(AVLTree tree)
{
    return HEIGHT(tree);
}

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

static Node *left_left_rotation(AVLTree keyRoot)
{   
    // 失去平衡的节点
    AVLTree keyTmp;

    keyTmp = keyRoot->left;
    keyRoot->left = keyTmp->right;
    keyTmp->right = keyRoot;

    keyRoot->height = MAX(HEIGHT(keyRoot->left), HEIGHT(keyRoot->right)) + 1;
    keyTmp->height =  MAX(HEIGHT(keyTmp->left), keyRoot->height) + 1;

    return keyTmp;
}

static Node *right_right_rotation(AVLTree keyRoot)
{
    // 失去平衡的节点
    AVLTree keyTmp;

    keyTmp = keyRoot->right;
    keyRoot->right = keyTmp->left;
    keyTmp->left = keyRoot;

    keyRoot->height = MAX(HEIGHT(keyRoot->left), HEIGHT(keyRoot->right)) + 1;
    keyTmp->height =  MAX(HEIGHT(keyTmp->right), keyRoot->height) + 1;

    return keyTmp;
}

/**
 * LR 旋转： 要恢复，先右单旋，后左单旋
 */
static Node *left_right_rotation(AVLTree keyRoot)
{
    keyRoot->left = right_right_rotation(keyRoot->left);

    return left_left_rotation(keyRoot);
}

static Node *right_left_rotation(AVLTree keyRoot)
{
    keyRoot->right = left_left_rotation(keyRoot->right);

    return right_right_rotation(keyRoot);
}

/**
 * 将结点插入AVL树，返回根节点
 */
Node *avltree_insert_node(AVLTree tree, Type key)
{
    if (NULL == tree)
    {
        tree = avltree_create_node(key, NULL, NULL);
        if (NULL == tree)
        {
            printf("[%s] 创建节点失败！\n");
            return NULL;
        }
    }
    else if (key > tree->key) // 插入的值大于节点的值，插入其右子树
    {
        tree->right = avltree_insert_node(tree->right, key);
        // 插入节点之后，检查树是否平衡
        if (HEIGHT(tree->right) - HEIGHT(tree->left) == 2)
        {
            if (key > tree->right->key)
            {
                tree = right_right_rotation(tree);
            }
            else
            {
                tree = right_left_rotation(tree);
            }
        }
    }
    else if (key < tree->key)
    {
        tree->left = avltree_insert_node(tree->left, key);
        if (HEIGHT(tree->left) - HEIGHT(tree->right) == 2)
        {
            if(key < tree->left->key)
            {
                tree = left_left_rotation(tree);
            }
            else
            {
                tree = left_right_rotation(tree);
            }
        }
    }
    else // 插入节点与树中节点相等
    {
        printf("该节点已存在!不允许添加相同节点！\n");
    }

    tree->height = MAX(HEIGHT(tree->left), HEIGHT(tree->right)) + 1;

    return tree;
}

/**
 * 递归实现
 * 查找书中值为 key的节点
 * @return      [返回找到的节点]
 */
Node *avltree_search(AVLTree tree, Type key)
{
    if(NULL == tree || tree->key == key)
    {
        return tree;
    }
    if (key < tree->key)
    {
        return avltree_search(tree->left, key);
    }
    else
    {
        return avltree_search(tree->right, key);
    }
}

/**
 * 循环实现
 * 查找书中值为 key的节点
 * @return      [返回找到的节点]
 */
Node *loop_avltree_search(AVLTree tree, Type key)
{
    AVLTree p = tree;

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

/**
 * 获取树中最大的节点
 * 最右边的节点最大
 * @param  tree [description]
 * @return      [description]
 */
Node *avltree_max_node(AVLTree tree)
{   
    Node *p = tree;
    if (tree == NULL)
    {
        return NULL;
    }

    while(p->right != NULL)
    {
        p = p->right;
    }

    return p;
}   

/**
 * 获取书中最小的节点
 * 最左边的节点最小
 * @param  tree [description]
 * @return      [description]
 */
Node *avltree_min_node(AVLTree tree)
{   
    Node *p = tree;
    if (tree == NULL)
    {
        return NULL;
    }

    while(p->left != NULL)
    {
        p = p->left;
    }

    return p;
}

/**
 * 删除节点
 * @param  tree [树根节点]
 * @param  node [被删除的节点]
 * @return      [返回根节点]
 */
Node *avltree_delete_node(AVLTree tree, Node *node)
{
    if (NULL == tree || NULL == node)
    {
        return tree;
    }

    // 要删除的节点在 tree节点的左子树
    if (node->key < tree->key)
    {
        tree->left = avltree_delete_node(tree->left, node);
        // 如果因为删除节点导致AVL树失去平衡
        if (HEIGHT(tree->right) - HEIGHT(tree->left) == 2)
        {
            // 删除左子树，导致右子树失衡
            Node *rTree = tree->right;
            if (HEIGHT(rTree->left) > HEIGHT(rTree->right))
            {
                tree = right_left_rotation(tree);
            }
            else
            {
                tree = right_right_rotation(tree);
            }
        }
    }
    else if (node->key > tree->key) // 要删除的节点在 tree节点的右子树
    {
        tree->right = avltree_delete_node(tree->right, node);
        if (HEIGHT(tree->left) - HEIGHT(tree->right) == 2)
        {
            // 删除右子树的节点，导致左子树失衡
            Node *lTree = tree->left;
            if (HEIGHT(lTree->right) > HEIGHT(lTree->left))
            {
                tree = left_right_rotation(tree);
            }
            else
            {
                tree = left_left_rotation(tree);
            }
        }
    }
    else // 要删除的节点就是根节点
    {
        // 如果树的左右子树都不为空
        if ((tree->left != NULL) && (tree->right != NULL))
        {
            if(HEIGHT(tree->left) > HEIGHT(tree->right))
            {
                // 左子树高于右子树
                //  找出左子树中最大的节点
                //  将最大节点的值赋值给tree
                //  将最大的节点删除
                Node *max = avltree_max_node(tree->left);
                tree->key = max->key;
                tree->left = avltree_delete_node(tree->left, max);
            }
            else
            {
                Node *min = avltree_min_node(tree->right);
                tree->key = min->key;
                tree->right = avltree_delete_node(tree->right, min);
            }
        }
        else
        {
            // 至少有一个子树为空
            Node *tmp = tree;
            tree = tree->left != NULL ? tree->left : tree->right;
            free(tmp);
        }
    }

    return tree;
}

/**
 * 根据key 值阐述树中的节点
 * @return      [返回根节点]
 */
Node *avltree_delete(AVLTree tree, Type key)
{
    Node * dst = avltree_search(tree, key);

    if (dst != NULL)
    {
        avltree_delete_node(tree, dst);
    }
    return tree;
}

/**
 * 销毁树
 * @param tree [description]
 */
void avltree_destroy(AVLTree tree)
{
    if (NULL == tree)
    {
        return;
    }

    if (tree->left)
    {
        avltree_destroy(tree->left);
    }
    if (tree->right)
    {
        avltree_destroy(tree->right);
    }

    free(tree);
}

/**
 * 打印树
 * @param tree      [节点]
 * @param key       [key]
 * @param direction [方向 0：根节点， -1： 左孩子， 1：右孩子]
 */
void avltree_print(AVLTree tree, Type key, int direction)
{
    if (tree == NULL)
    {
        return ;
    }

    if (direction == 0)
    {
        printf("%3d is root.\n", tree->key);
    }
    else
    {
        printf("%3d is %3d’s %6s child\n", tree->key, key, direction == 1 ? "right" : "left");
    }

    avltree_print(tree->left, tree->key, -1);
    avltree_print(tree->right, tree->key, 1);
}

// 前根序遍历
void pre_order_bstree(AVLTree tree)
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
void middle_order_bstree(AVLTree tree)
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
void behind_order_bstree(AVLTree tree)
{
    if (NULL == tree)
    {
        return ;
    }

    behind_order_bstree(tree->left);
    behind_order_bstree(tree->right);
    printf("%d ", tree->key);
}

static int arr[]= {3,2,1,4,5,6,7,16,15,14,13,12,11,10,8,9};

#define ARRAY_SIZE(a) ( (sizeof(a)) / (sizeof(a[0])) )

int main(int argc, char const *argv[])
{
    AVLTree root = NULL;

    int i = 0;
    printf("== 高度: %d\n", avltree_height(root));
    printf("--> 新建结点: ");
    for (i=0; i < ARRAY_SIZE(arr); ++i)
    {   
        printf("%d ", arr[i]);
        root = avltree_insert_node(root, arr[i]);
    }

    printf("\n--> 前序遍历: ");
    pre_order_bstree(root);

    printf("\n--> 中序遍历: ");
    middle_order_bstree(root);

    printf("\n--> 后序遍历: ");
    behind_order_bstree(root);

    printf("\n");
    printf("== 高度: %d\n", avltree_height(root));
    printf("== 最小值: %d\n", avltree_min_node(root)->key);
    printf("== 最大值: %d\n", avltree_max_node(root)->key);
    printf("== 树的详细信息: \n");
    avltree_print(root, root->key, 0);

    int j = 0;
    for ( ; j < 5; j++)
    {
        int tmp = rand() % 100;
        root = avltree_insert_node(root, tmp);
    }
    
    printf("\n");
    printf("== 高度: %d\n", avltree_height(root));
    printf("== 最小值: %d\n", avltree_min_node(root)->key);
    printf("== 最大值: %d\n", avltree_max_node(root)->key);
    printf("== 树的详细信息: \n");
    avltree_print(root, root->key, 0);

    root = avltree_delete(root, 11);
    printf("\n");
    printf("== 高度: %d\n", avltree_height(root));
    printf("== 最小值: %d\n", avltree_min_node(root)->key);
    printf("== 最大值: %d\n", avltree_max_node(root)->key);
    printf("== 树的详细信息: \n");
    avltree_print(root, root->key, 0);

    avltree_destroy(root);

    return 0;
}
