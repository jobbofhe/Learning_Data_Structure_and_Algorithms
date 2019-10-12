/*
* @Author: jobbofhe
* @Date:   2019-10-12 15:58:07
* @Last Modified by:   Administrator
* @Last Modified time: 2019-10-12 18:55:10
*/

#include <stdio.h>
#include <stdlib.h>

typedef int Type;

typedef struct HuffmanNode_
{
    Type  weight; // 节点权重
    Type  parent, left, right; //父结点、左孩子、右孩子在数组中的位置下标

}Node, *HuffmanTree; 

void select(HuffmanTree HT, int *pos1, int *pos2, int end)
{
    int min1 = 0, min2 = 0;

    int i = 1; // 数组的 0 号元素作为根节点的位置所以不使用

    // 找到没有构建成树的第一个节点
    while (HT[i].parent != 0 && i <= end)
    {
        i++;
    }
    min1 = HT[i].weight;
    *pos1 = i;

    i++;
    // 找到没有构建成树的第二个节点
    while(HT[i].parent != 0 && i <= end) 
    {
        i++;
    }

    min2 = HT[i].weight;
    if (min2 < min1)
    {
        min2 = min1;
        *pos2 = *pos1;
        min1 = HT[i].weight;
        *pos1 = i;
    }
    else
    {
        *pos2 = i;
    }

    // 取得两个节点之后，跟之后所有没有构建成树的节点逐一比较，最终获取最小的两个节点
    for (int j = i+1; j <= end; ++j)
    {
        // 如果已经存在父节点，也就是已经被构建树了，则跳过
        if (HT[j].parent != 0)
        {
            continue;
        }

        // 如果比min1 还小，将min2 = 敏, min1修改为新的节点下标
        if (HT[j].weight < min1)
        {
            min2 = min1;
            min1 = HT[j].weight;
            *pos2 = *pos1;
            *pos1 = j;
        }
        else if (HT[j].weight < min2 && HT[j].weight > min1)
        {
            // 如果大于 min1 小于 min2
            min2 = HT[j].weight;
            *pos2 = j;
        }
    }
}

HuffmanTree init_huffman_tree(Type *weight, int node_num)
{
    if (node_num <= 1)
    {
        // 只有一个节点那么编码就是 0
        return NULL;
    }

    int tree_node_num = node_num * 2 - 1; // 根节点不使用
    HuffmanTree p = (HuffmanTree)malloc((tree_node_num+1) * sizeof(Node));

    // 初始化哈夫曼数组中的所有节点
    for (int i = 1; i <= tree_node_num; ++i)
    {        
        if (i <= node_num)
        {
            (p+i)->weight = *(weight+i-1); // 第0个位置不使用
        }
        else
        {
            (p+i)->weight = 0;
        }

        (p+i)->parent = 0;
        (p+i)->left = 0;
        (p+i)->right = 0;
    }

    return p;
}

void close_huffman_tree(HuffmanTree HT)
{
    if (HT)
    {
        free(HT);
        HT = NULL;
    }
}

void create_huffman_tree(HuffmanTree HT, int node_num)
{
    if (NULL == HT || node_num <= 1)
    {
        return;
    }

    int tree_node_num = node_num * 2 - 1; // 根节点不使用
    for (int i = node_num + 1; i <= tree_node_num; ++i)
    {
        int pos1 = -1, pos2 = -1;
        // 找到频率最小的连个节点
        select(HT, &pos1, &pos2, i-1);
        printf("当前最小的两个节点 [%4d %4d]\n", HT[pos1].weight, HT[pos2].weight);
        // 这里使用下表来表示父子关系
        HT[pos1].parent = HT[pos2].parent = i; // pos1 位置的元素和pos2位置的元素 的父节点就是，第 i个位置的元素
        HT[i].left = pos1;  // 父节点的左后孩子赋值
        HT[i].right = pos2;
        HT[i].weight = HT[pos1].weight + HT[pos2].weight; // 父节点的权重等于 左右孩子权重的和
    }
}

void print(HuffmanTree HT, int node_num)
{
    if (NULL == HT)
    {
        printf("数组为空\n");
        return;
    }

    int tree_node_num;

    for (int i = 1; i < tree_node_num; ++i)
    {
        printf("节点 %3d 的父节点：%4d 左孩子：%4d 右孩子：%4d\n", HT[i].weight, HT[HT[i].parent].weight, HT[i].left, HT[i].right);
    }

}

int main(int argc, char const *argv[])
{
    
    Type weight[8] = {80, 30, 20, 75, 40, 8, 55, 60};

    int node_num = sizeof(weight) / sizeof(Type);

    HuffmanTree HT = init_huffman_tree(weight, node_num);

    create_huffman_tree(HT, node_num);

    print(HT, node_num);

    close_huffman_tree(HT);

    return 0;
}