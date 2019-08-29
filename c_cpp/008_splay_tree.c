/*
* @Author: jobbofhe
* @Date:   2019-08-29 10:03:17
* @Last Modified by:   Administrator
* @Last Modified time: 2019-08-29 10:40:52
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


// 节点定义
typedef int Type;

typedef struct SplayTreeNode
{
    Type key;
    struct SplayTreeNode left;
    struct SplayTreeNode right;

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

Node *splaytree_search_max(SplayTree tree);

Node *splaytree_search_min(SplayTree tree);

Node *splaytree_splay(SplayTree tree, Type key);

Node *splaytree_insert(SplayTree tree, Type key);

Node *splaytree_delete(SplayTree tree, Type key);

void splaytree_print(SplayTree tree);

void splaytree_destroy(SplayTree tree);

static Node *create_node(Type key, Node *left, Node *right);


int main(int argc, char const *argv[])
{
    
    return 0;
}