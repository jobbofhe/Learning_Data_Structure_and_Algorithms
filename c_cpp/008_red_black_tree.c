/*
* @Author: jobbofhe
* @Date:   2019-09-11 21:01:00
* @Last Modified by:   Administrator
* @Last Modified time: 2019-09-24 16:13:38
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

/**
 * 循环实现查找
 * @return      [返回找到的节点，否则返回NULL]
 */
static Node *search_loop(RBTree tree, Type key);

/**
 * 循环实现，查找树中的key值的点
 * @return      [找到返回 0，  未找到返回 -1]
 */
int rbtree_search_loop(RBRoot *root, Type key);

/**
 * 查找最小节点
 * @return      [找到返回节点，未找到返回空]
 */
static Node *search_min(RBTree tree);

/**
 * 查找树中最小的值， 
 * @param  min_key [出书参数，如果找到，传出]
 * @return         [找到返回0， 否则返回 -1]
 */
int rbtree_search_min(RBRoot *root, int *min_key);


/**
 * 查找最大节点
 * @return      [找到返回节点，未找到返回空]
 */
static Node *search_max(RBTree tree);

/**
 * 查找树中最大的值， 
 * @param  min_key [出书参数，如果找到，传出]
 * @return         [找到返回0， 否则返回 -1]
 */
int rbtree_search_max(RBRoot *root, int *max_key);

/**
 * 查找当前节点的后继结点,
 * 后继结点：即是红黑树中数据值大于 【当前节点】值的所有节点中的【最小节点】
 * @param  cur_node [当前节点]
 * @return          [如果找到返回后继结点，否则返回NULL]
 */
static Node *rbtree_search_successor(RBTree cur_node);

/**
 * 查找当前节点的前驱节点
 * 前驱节点： 红黑树中数据值小于【当前节点】的所有节点汇总的【最大的节点】
 * @param  cur_node [当前节点]
 * @return          [如果找到返回前驱节点，否则返回NULL]
 */
static Node *rbtree_search_predecessor(RBTree cur_node);

/* 
 * 对红黑树的节点(x)进行左旋转
 *
 * 左旋示意图(对节点x进行左旋)：
 *      px                              px
 *     /                               /
 *   node                             y                
 *   /  \      --(左旋)-->           / \                
 *  lx   y                        node ry     
 *     /   \                       /    \
 *    ly   ry                     lx    ly  
 *
 */
static void rbtree_left_rotate(RBRoot *root, Node *node);

/* 
 * 对红黑树的节点(y)进行右旋转
 *
 * 右旋示意图(对节点y进行左旋)：
 *            py                               py
 *           /                                /
 *         node                              x                 
 *         /  \      --(右旋)-->            /  \                     
 *        x   ry                           lx  node
 *       / \                                   /  \                   
 *      lx  rx                                rx  ry
 * 
 */
static void rbtree_right_rotate(RBRoot *root, Node *y);


/**
 * 当初插入显得节点之后（如果失去平衡），调用该函数，将失衡的红黑树 重新构造为红黑树
 * @param root [红黑树的根]
 * @param z    [插入的节点]
 */
static void rbtree_insert_fixup(RBRoot *root, Node *z);

/**
 * 将新节点 node 插入到红黑树中
 * @param root [根]
 * @param node [新节点]
 */
static void rbtree_insert_node(RBRoot *root, Node *node);

/**
 * 创建红黑树的一个节点
 * @param  key    [值]
 * @param  parent [父节点]
 * @param  left   [左孩子]
 * @param  right  [右孩子]
 * @return        [返回创建好的节点]
 */
static Node *create_node(Type key, Node *parent, Node *left, Node *right);

/**
 * 将 数值 key（创建节点之后）插入到书中
 * @param  key [值]
 * @return     [成功返回0， 失败返回 -1]
 */
int rbtree_insert(RBRoot *root, Type key);

/**
 * 因为删除节点 造成红黑树失衡，本函数矫正，使得该树重新变为红黑树
 * @param root      [树根]
 * @param node      [待修正的节点]
 * @param parent    [待修正的节点]
 */
static void rbtree_delete_fixup(RBRoot *root, Node *node, Node *parent);

/**
 * 红黑树删除节点
 * @param root [树根]
 * @param node [要删除的节点]
 */
void rbtree_delete_node(RBRoot *root, Node *node);

/* 
 * 删除键值为key的结点
 *
 * 参数说明：
 *     tree 红黑树的根结点
 *     key 键值
 */
void rbtree_delete(RBRoot *root, Type key);

/**
 * 销毁红黑树
 */
static void rbtree_destroy_tree(RBTree tree);

void rbtree_destroy(RBRoot *root);

/*
 * 打印"红黑树"
 *
 * tree       -- 红黑树的节点
 * key        -- 节点的键值 
 * direction  --  0，表示该节点是根节点;
 *               -1，表示该节点是它的父结点的左孩子;
 *                1，表示该节点是它的父结点的右孩子。
 */
static void rbtree_print(RBTree tree, Type key, int direction);

void print_rbtree(RBRoot *root);


// 函数定义


void print_rbtree(RBRoot *root)
{
    if (root!=NULL && root->node!=NULL)
    {
        rbtree_print(root->node, root->node->key, 0);
    }
}

static void rbtree_print(RBTree tree, Type key, int direction)
{
    if(tree != NULL)
    {
        if(direction==0)    // tree是根节点
        {
            printf("%2d(B) is root\n", tree->key);
        }
        else                // tree是分支节点
        {
            printf("%2d(%s) is %4d's %6s child\n", tree->key, RB_IS_RED(tree)?"R":"B", key, direction==1?"right" : "left");
        }

        rbtree_print(tree->left, tree->key, -1);
        rbtree_print(tree->right,tree->key,  1);
    }
}

void rbtree_destroy(RBRoot *root)
{
    if(root)
    {
        rbtree_destroy_tree(root->node);
    }
}

static void rbtree_destroy_tree(RBTree tree)
{
    if (tree == NULL)
    {
        return;
    }

    if (tree->left != NULL)
    {
        rbtree_destroy_tree(tree->left);
    }
    if (tree->right != NULL)
    {
        rbtree_destroy_tree(tree->right);
    }

    free(tree);
}


void rbtree_delete_node(RBRoot *root, Node *node)
{
    Node *child, *parent;
    int color;

    // 被删除节点的"左右孩子都不为空"的情况。
    if ( (node->left!=NULL) && (node->right!=NULL) ) 
    {
        // 被删节点的后继节点。(称为"取代节点")
        // 用它来取代"被删节点"的位置，然后再将"被删节点"去掉。
        Node *replace = node;

        // 获取后继节点
        replace = replace->right;
        while (replace->left != NULL)
        {
            replace = replace->left;
        }

        // "node节点"不是根节点(只有根节点不存在父节点)
        if (RB_PARENT(node))
        {
            if (RB_PARENT(node)->left == node)
            {
                RB_PARENT(node)->left = replace;
            }
            else
            {
                RB_PARENT(node)->right = replace;
            }
        } 
        else 
        {
            // "node节点"是根节点，更新根节点。
            root->node = replace;
        }

        // child是"取代节点"的右孩子，也是需要"调整的节点"。
        // "取代节点"肯定不存在左孩子！因为它是一个后继节点。
        child = replace->right;
        parent = RB_PARENT(replace);
        // 保存"取代节点"的颜色
        color = RB_COLOR(replace);

        // "被删除节点"是"它的后继节点的父节点"
        if (parent == node)
        {
            parent = replace;
        } 
        else
        {
            // child不为空
            if (child)
            {
                RB_SET_PARENT(child, parent);
            }
            parent->left = child;

            replace->right = node->right;
            RB_SET_PARENT(node->right, replace);
        }

        replace->parent = node->parent;
        replace->color = node->color;
        replace->left = node->left;
        node->left->parent = replace;

        if (color == BLACK)
        {
            rbtree_delete_fixup(root, child, parent);
        }
        free(node);

        return ;
    }

    if (node->left !=NULL)
    {
        child = node->left;
    }
    else 
    {
        child = node->right;
    }

    parent = node->parent;
    // 保存"取代节点"的颜色
    color = node->color;

    if (child)
    {
        child->parent = parent;
    }

    // "node节点"不是根节点
    if (parent)
    {
        if (parent->left == node)
        {
            parent->left = child;
        }
        else
        {
            parent->right = child;
        }
    }
    else
    {
        root->node = child;
    }

    if (color == BLACK)
    {
        rbtree_delete_fixup(root, child, parent);
    }
    free(node);
}

/* 
 * 删除键值为key的结点
 *
 * 参数说明：
 *     tree 红黑树的根结点
 *     key 键值
 */
void rbtree_delete(RBRoot *root, Type key)
{
    Node *z, *node; 

    if ((z = search(root->node, key)) != NULL)
        rbtree_delete_node(root, z);
}

static void rbtree_delete_fixup(RBRoot *root, Node *node, Node *parent)
{
    Node *tmp;

    // 如果被旋转的节点不是根节点，并且是黑色或者为空时
    while ((!node || RB_IS_BLACK(node)) && node != root->node)
    {
        if (parent->left == node)
        {
            tmp = parent->right;
            if (RB_IS_RED(tmp))
            {
                // Case 1: node的兄弟w是红色的  
                RB_SET_BLACK(tmp);
                RB_SET_RED(parent);
                rbtree_left_rotate(root, parent);
                tmp = parent->right;
            }
            if ((!tmp->left || RB_IS_BLACK(tmp->left)) &&
                (!tmp->right || RB_IS_BLACK(tmp->right)))
            {
                // Case 2: node的兄弟w是黑色，且w的俩个孩子也都是黑色的  
                RB_SET_RED(tmp);
                node = parent;
                parent = RB_PARENT(node);
            }
            else
            {
                if (!tmp->right || RB_IS_BLACK(tmp->right))
                {
                    // Case 3: node的兄弟w是黑色的，并且w的左孩子是红色，右孩子为黑色。  
                    RB_SET_BLACK(tmp->left);
                    RB_SET_RED(tmp);
                    rbtree_right_rotate(root, tmp);
                    tmp = parent->right;
                }
                // Case 4: node的兄弟w是黑色的；并且w的右孩子是红色的，左孩子任意颜色。
                RB_SET_COLOR(tmp, RB_COLOR(parent));
                RB_SET_BLACK(parent);
                RB_SET_BLACK(tmp->right);
                rbtree_left_rotate(root, parent);
                node = root->node;
                break;
            }
        }
        else
        {
            tmp = parent->left;
            if (RB_IS_RED(tmp))
            {
                // Case 1: node的兄弟w是红色的  
                RB_SET_BLACK(tmp);
                RB_SET_RED(parent);
                rbtree_right_rotate(root, parent);
                tmp = parent->left;
            }
            if ((!tmp->left || RB_IS_BLACK(tmp->left)) &&
                (!tmp->right || RB_IS_BLACK(tmp->right)))
            {
                // Case 2: node的兄弟w是黑色，且w的俩个孩子也都是黑色的  
                RB_SET_RED(tmp);
                node = parent;
                parent = RB_PARENT(node);
            }
            else
            {
                if (!tmp->left || RB_IS_BLACK(tmp->left))
                {
                    // Case 3: node的兄弟w是黑色的，并且w的左孩子是红色，右孩子为黑色。  
                    RB_SET_BLACK(tmp->right);
                    RB_SET_RED(tmp);
                    rbtree_left_rotate(root, tmp);
                    tmp = parent->left;
                }
                // Case 4: node的兄弟w是黑色的；并且w的右孩子是红色的，左孩子任意颜色。
                RB_SET_COLOR(tmp, RB_COLOR(parent));
                RB_SET_BLACK(parent);
                RB_SET_BLACK(tmp->left);
                rbtree_right_rotate(root, parent);
                node = root->node;
                break;
            }
        }
    }
    if (node)
    {
        RB_SET_BLACK(node);
    }
}

int rbtree_insert(RBRoot *root, Type key)
{
    Node *node = NULL;

    // 不允许插入相同的节点，首先查找朝如的数据是否已经存在
    if (search(root->node, key) != NULL)
    {
        return -1;
    }

    node = create_node(key, NULL, NULL, NULL);
    if (node == NULL)
    {
        return -1;
    }

    rbtree_insert_node(root, node);

    return 0;

}

static Node *create_node(Type key, Node *parent, Node *left, Node *right)
{
    Node *p = (Node *)malloc(sizeof(Node));

    if (p == NULL)
    {
        return NULL;
    }

    p->key = key;
    p->parent = parent;
    p->left = left;
    p->right = right;
    p->color = BLACK;

    return p;
}

/**
 * 思路：
 * 1. 找到要插入的位置，通过比较节点的key 值 大小
 * 2. 找到位置之后， 将找到的节点y 设置为新节点的父节点
 *     2.1 如果找到的节点 y 是空的， 即树为空，那么新的节点就设置为根节点
 *     2.2 如果找到节点Y不为空，则 判确定新节点 是节点 y的那个孩子
 * 3. 着色，一般的将插入的节点颜色，全部标为 红色
 * 4. 修正因插入导致的 红黑树失衡问题
 */
static void rbtree_insert_node(RBRoot *root, Node *node)
{
    Node *y = NULL;
    Node *p = root->node;


    // 找到要插入的位置
    while(p != NULL) 
    {
        y = p;
        if (node->key < p->key)
        {
            p = p->left;
        }
        else
        {
            p = p->right;
        }
    }

    // 找到y 是要插入的位置
    // 将新节点的父节点 设置为y
    RB_PARENT(node) = y;

    // 确定要插入的节点node 是 y的那个(左还是右)孩子
    if (y != NULL)
    {
        if (node->key < y->key)
        {
            y->left = node;
        }
        else
        {
            y->right = node;
        }
    }
    else
    {
        // 如果没有找到 查找的位置，将node节点作为根节点
        root->node = node;
    }

    // 插入之后，确定节点的颜色
    node->color = RED;

    rbtree_insert_fixup(root, node);
}

/**
 * 思路：
 * 因插入导致红黑树失衡的解决思路
 * 1. 插入节点之后，如果父节点不存在，即插入的节点就是树根，那么将其设置为黑色
 * 2. 如果父节点存在，并且是【红色】
 *     2.1 如果父节点 是 祖父节点 的【左孩子】
 *         2.1.1 如果叔叔节点存在，则叔叔节点是祖父节点的【右孩子】，并且此时叔叔节点 如果 是 【红色】
 *               此时将 叔叔节点 和 父亲节点都设置 为【黑色】，并且将 祖父节点设置 为 【红色】
 *               如果叔叔节点是黑色， 并且新插入的节点是父节点的右孩子
 *                   左旋
 *               如果叔叔节点是黑色， 并且新插入的节点是父节点的左孩子
 *                   右旋
 *     2.2 如果父节点 是 祖父节点 的右孩子
 *         与上旋转相反
 * 3. 如果费节点存在，并且父节点是黑色，则树有效，不需要旋转
 *
 *
 * 红黑树插入的几种情况：
 * 情况1，z的叔叔y是红色的。
 * 情况2：z的叔叔y是黑色的，且z是右孩子
 * 情况3：z的叔叔y是黑色的，且z是左孩子
 * 
 */
static void rbtree_insert_fixup(RBRoot *root, Node *z)
{
    Node *parent, *gparent;

    // 如果父节点存在，并且父节点的颜色是红色
    while((parent = RB_PARENT(z)) && RB_IS_RED(parent)) 
    {
        gparent = RB_PARENT(parent);

        // 如果父节点是祖父节点的左孩子
        if (gparent->left == parent)
        {
            {
                Node *uncle_node = gparent->right;
                // 如果叔叔节点存在， 并且为红色
                if (uncle_node && RB_IS_RED(uncle_node))
                {
                    RB_SET_BLACK(uncle_node);
                    RB_SET_BLACK(parent);
                    RB_SET_RED(gparent);
                    z = gparent;
                    continue;
                }
            }

            // 叔叔节点是黑色，并且当前节点z是右孩子
            if (parent->right == z)
            {
                Node *tmp;
                rbtree_left_rotate(root, parent);
                tmp = parent;
                parent = z;
                z = tmp;
            }

            // 叔叔节点是黑色，并且当前节点是 左孩子
            RB_SET_BLACK(parent);
            RB_SET_RED(gparent);
            rbtree_right_rotate(root, gparent);
        }
        else  // 如果父节点是祖父节点的右孩子
        {
            // 叔叔节点存在，并且是红色
            {
                Node *uncle_node = gparent->left;
                if (uncle_node && RB_IS_RED(uncle_node))
                {
                    RB_SET_BLACK(uncle_node);
                    RB_SET_BLACK(parent);
                    RB_SET_RED(gparent);
                    z = gparent;
                    continue;
                }
            }

            // 叔叔节点是黑色，并且当前节点 z 是左孩子
            if (parent->left == z)
            {
                Node *tmp ;
                rbtree_right_rotate(root, parent);
                tmp = parent;
                parent = z;
                z = tmp;
            }

            // 叔叔节点是黑色，并且当前节点 z 是右孩子
            RB_SET_BLACK(parent);
            RB_SET_RED(gparent);
            rbtree_left_rotate(root, gparent);

        }
    }

    RB_SET_BLACK(root->node);
}

/* 
 * 对红黑树的节点(node)进行右旋转
 *
 * 右旋示意图(对节点node进行左旋)：
 *            py                               py
 *           /                                /
 *         node                              x                 
 *         /  \      --(右旋)-->            /  \                     
 *        x   ry                           lx  node
 *       / \                                   /  \                   
 *      lx  rx                                rx  ry
 * 
 */
static void rbtree_right_rotate(RBRoot *root, Node *node)
{
    // 创建临时变量，保存被旋转的节点的左孩子
    Node *x = node->left;

    // ---1 处理 node 和 其左孩子
    // 开始旋转， node 下移，则node的左孩子变为 x的右孩子
    node->left = x->right;

    // 如果x的节点存在右孩子，则将右孩子设置为 node的左孩子
    if (x->right != NULL)
    {
        x->right->parent = node;
    }

    // ---2 处理被旋转节点 与 其父节点
    // x 的父节点发生变化
    x->parent = node->parent;

    // 被旋转的节点没有父节点
    if (node->parent == NULL)
    {
        // 如果被旋转的节点就是根节点，则新的根节点变为选准后的根节点
        root->node = x;
    }
    else
    {
        // 被旋转的节点是器 父节点的左孩子
        if (node->parent->left == node)
        {
            node->parent->left = x;
        }
        else // 被旋转的节点是器 父节点的右孩子
        {
            node->parent->right = x;
        }
    }
    
    // ---3 处理 被旋转节点和 X
    x->right = node;
    node->parent = x;
}

/* 
 * 对红黑树的节点(node)进行左旋转
 *
 * 左旋示意图(对节点node进行左旋)：
 *      px                              px
 *     /                               /
 *   node                             y                
 *   /  \      --(左旋)-->           / \                
 *  lx   y                        node ry     
 *     /   \                       /    \
 *    ly   ry                     lx    ly  
 *
 */
static void rbtree_left_rotate(RBRoot *root, Node *node)
{   
    // 将node的右孩子赋值给 y
    Node *y = node->right;

    // node 下移，y的左孩子赋值给 node的右孩子
    node->right = y->left;

    // 如果 y存在左孩子， 则将y的左孩子的父节点设置为 node
    if (y->left != NULL)
    {
        y->left->parent = node;
    }

    // node的父结点 设为 y的父节点，即让px指向 y
    y->parent = node->parent;

    if (node->parent == NULL)
    {
        // y 就是根节点
        root->node = y;
    }
    else
    {
        if (node->parent->left == node)
        {
            // 如果被旋转的节点node的父节点不为空，并且被旋转的节点node是其父节点的左孩子，则将y设置为node的父节点的组左孩子
            node->parent->left = y;
        }
        else
        {
            // 如果被旋转的节点node的父节点不为空，并且被旋转的节点node是其父节点的右孩子，则将y设置为node的父节点的组右孩子
            node->parent->right = y;
        }
    }
    
    y->left= node;
    node->parent = y;
}

static Node *rbtree_search_predecessor(RBTree cur_node)
{
    // 如果 当前节点的左孩子不为空，那么 节点 cur_node 的前驱结点就是 以 cur_node 为根节点的的子树的 最大节点
    if (cur_node->left != NULL)
    {
        return search_max(cur_node->left);
    }

    // 如果没有左孩子
    // 1. 如果 cur_node 是右孩子，则其父节点 就是前驱节点
    // 2. 如果 cur_node 是左孩子，则查找 cur_node的最低父节点，并且这个父节点要有 右孩子，那么这个最低父节点就是 cur_node的前驱节点
    Node *tmp = cur_node->parent;

    while ((tmp != NULL) && (cur_node == tmp->left))
    {
        cur_node = tmp;
        tmp = tmp->parent;
    }

    return tmp;
}

static Node *rbtree_search_successor(RBTree cur_node)
{
    // 如果 当前节点的右孩子不为空，那么 节点 cur_node 的后继结点就是 以 cur_node 为根节点的的子树的 最小节点
    if (cur_node->right != NULL)
    {
        return search_min(cur_node->right);
    }

    // 如果没有右孩子
    // 1. 如果cur_node 是一个左孩子，则其父节点就是他的 后继结点
    // 2. 如果cur_node 是一个右孩子，则查找 cur_node的最低父节点，并且这个父节点要有左孩子，那么这个最低的父节点就是 cur_node的后继结点
    Node *tmp = cur_node->parent;

    // 如果当前节点的父节点不为空，并且当前节是右节点
    while((tmp != NULL) && (cur_node == tmp->right)) 
    {
        cur_node = tmp;
        tmp = tmp->parent;
    }

    return tmp;
}

int rbtree_search_max(RBRoot *root, int *max_key)
{
    Node *node = NULL;

    if (root)
    {
        node = search_max(root->node);
    }

    if (node)
    {
        *max_key = node->key;

        return 0;
    }
    else
    {
        return -1;
    }
}


static Node *search_max(RBTree tree)
{
    if (NULL == tree)
    {
        return NULL;
    }

    RBTree p = tree;

    while(p->right != NULL) 
    {
        p = p->right;
    }

    return p;
}


int rbtree_search_min(RBRoot *root, int *min_key)
{
    Node *node = NULL;

    if (root)
    {
        node = search_min(root->node);
    }

    if (node)
    {
        *min_key = node->key;

        return 0;
    }
    else
    {
        return -1;
    }

}

static Node *search_min(RBTree tree)
{
    if (NULL == tree)
    {
        return NULL;
    }

    RBTree p = tree;

    while (NULL != p->left)
    {
        p = p->left;
    }

    return p;

}

static Node *search_loop(RBTree tree, Type key)
{
    RBTree p = tree;

    while((p != NULL) && (p->key != key)) 
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
 * 循环实现，查找树中的key值的点
 * @return      [找到返回 0，  未找到返回 -1]
 */
int rbtree_search_loop(RBRoot *root, Type key)
{
    if (root)
    {
        if (search_loop(root->node, key) != NULL)
        {
            return 0;
        }
        else
        {
            return -1;
        }
    }
}

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
        // printf("Red tree is empty!\n");
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
        // printf("Red tree is empty!\n");
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
        // printf("Red tree is empty!\n");
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

#define LENGTH(a) ( (sizeof(a)) / (sizeof(a[0])) )

#define SWITCH_INSERT 1    // 打印插入信息开关(0，关闭；1，打开)
#define SWITCH_DELETE 1    // 打印删除信息开关(0，关闭；1，打开)

int main(int argc, char const *argv[])
{
    
    int a[] = {11, 41, 32, 62, 93, 73, 24, 54, 85};
    int i, ilen=LENGTH(a);
    RBRoot *root=NULL;

    root = create_rbtree();
    printf("------ 原始数据: ");
    for(i=0; i<ilen; i++)
    {
        printf("%d ", a[i]);
    }
    printf("\n");

    for(i=0; i<ilen; i++)
    {
        rbtree_insert(root, a[i]);
#if SWITCH_INSERT
        printf("------ 添加节点: %d\n", a[i]);
        printf("------ 树的详细信息: \n");
        print_rbtree(root);
        printf("\n");
#endif
    }

    printf("------ 前序遍历: ");
    rbtree_preorder(root->node);

    printf("\n------ 中序遍历: ");
    rbtree_inorder(root->node);

    printf("\n------ 后序遍历: ");
    rbtree_behindorder(root->node);
    printf("\n");

    if (rbtree_search_min(root, &i)==0)
        printf("------ 最小值: %d\n", i);
    if (rbtree_search_max(root, &i)==0)
        printf("------ 最大值: %d\n", i);
    printf("------ 树的详细信息: \n");
    print_rbtree(root);
    printf("\n");

#if SWITCH_DELETE
    for(i=0; i<ilen; i++)
    {
        rbtree_delete(root, a[i]);

        printf("------ 删除节点: %d\n", a[i]);
        if (root)
        {
            printf("------ 树的详细信息: \n");
            print_rbtree(root);
            printf("\n");
        }
    }
#endif

    rbtree_destroy(root);
}