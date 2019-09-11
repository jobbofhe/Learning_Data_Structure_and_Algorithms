/*
* @Author: jobbofhe
* @Date:   2019-09-11 21:01:00
* @Last Modified by:   Administrator
* @Last Modified time: 2019-09-11 21:11:32
*/

/**
 * 数据结构定义
 */

#define RED     (0)
#define BLACK   (1)

typedef int Type;

typedef struct RBTreeNode
{
    int color;
    Type key;
    struct RBTreeNode *left;
    struct RBTreeNode *right;
    struct RBTreeNode *parent;

}Node, *RBTree;


/**
 * 函数声明
 */



/**
 * 函数定义
 */



/**
 * 测试
 */

int main(int argc, char const *argv[])
{
    /* code */
    return 0;
}