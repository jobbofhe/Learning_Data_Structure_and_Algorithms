/*
* @Author: jobbofhe
* @Date:   2019-11-01 16:44:27
* @Last Modified by:   Administrator
* @Last Modified time: 2019-11-05 09:45:09
*/

#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>

#define  IS_LETTER(c)   ( (((c) >= 'a') && ((c) <= 'z')) || (((c) >= 'A') && ((c) <= 'Z')) )
#define  LENGTH(c)      (sizeof(c)/(sizeof(c[0])))

#define MAX_VERTEX (200)

// 邻接表链表中的节点
typedef struct Node_
{
    int index_vex;
    struct Node_ *next_edge;

}Node, *pNode;

// graph 顶点信息
typedef struct VertexNode_
{
    char data;
    Node *first_edge;

}VertexNode;

// 邻接表结构体
typedef struct ListListGraph_
{
    int vertex_number;
    int edge_number;
    VertexNode vertex[MAX_VERTEX];

}ListGraph;

int get_position(ListGraph list_graph, char ch)
{
    for (int i = 0; i < list_graph.vertex_number; ++i)
    {
        if (list_graph.vertex[i].data == ch)
        {
            return i;
        }
    }

    return -1;
}

void append_tail(Node *list, Node *node)
{
    Node *p = list;

    while(p->next_edge) 
    {
        p = p->next_edge;
    }
    p->next_edge = node;
}

/*
 * 创建图(用已提供的矩阵)
 */
ListGraph* create_graph(char *vertex, char edges[][2], int vlen, int elen)
{
    int i, p1, p2;
    Node *node1, *node2;
    ListGraph* pG;
    
    if ((pG=(ListGraph*)malloc(sizeof(ListGraph))) == NULL )
    {
        return NULL;
    }
    memset(pG, 0, sizeof(ListGraph));

    // 初始化"顶点数"和"边数"
    pG->vertex_number = vlen;
    pG->edge_number = elen;
    printf("顶点数量： %d  边数 :%d\n", vlen, elen);
    // 初始化"顶点"
    for (i = 0; i < pG->vertex_number; i++)
    {
        pG->vertex[i].data = vertex[i];
        pG->vertex[i].first_edge = NULL;
    }

    // 初始化"边"
    for (i = 0; i < pG->edge_number; i++)
    {
        // 读取边的起始顶点和结束顶点
        p1 = get_position(*pG, edges[i][0]);
        p2 = get_position(*pG, edges[i][1]);

        // A-->B
        node1 = (Node *)malloc(sizeof(Node));
        node1->index_vex = p2;
        // 将node1, 插在链表末尾
        if (pG->vertex[p1].first_edge == NULL)
        {
            pG->vertex[p1].first_edge = node1;
        }
        else
        {
            append_tail(pG->vertex[p1].first_edge, node1);
        }

        // B-->A
        node2 = (Node *)malloc(sizeof(Node));
        node2->index_vex = p1;
        if (pG->vertex[p2].first_edge == NULL)
        {
            pG->vertex[p2].first_edge = node2;
        }
        else
        {
            append_tail(pG->vertex[p2].first_edge, node2);
        }
    }

    return pG;
}

void print_graph(ListGraph graph)
{
    printf("顶点数量： %d\n", graph.vertex_number);


    for (int i = 0; i < graph.vertex_number; ++i)
    {
        printf("[%d](%c)", i, graph.vertex[i].data);
        Node *node = graph.vertex[i].first_edge;
        while(node != NULL) 
        {
            printf("-->[%d](%c)", node->index_vex, graph.vertex[node->index_vex].data);
            node = node->next_edge;
        }

        printf("\n");
    }
}

int main(int argc, char const *argv[])
{
    char vertex[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H'};
    char edges[][2] = {
        {'A', 'C'}, 
        {'A', 'D'}, 
        {'A', 'F'}, 
        {'B', 'C'}, 
        {'C', 'D'}, 
        {'F', 'G'},
        {'G', 'E'},
        {'E', 'H'}}; 

    ListGraph* p_graph_2 = create_graph(vertex, edges, LENGTH(vertex), LENGTH(edges));
    print_graph(*p_graph_2);
    return 0;
}