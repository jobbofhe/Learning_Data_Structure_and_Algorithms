/*
* @Author: jobbofhe
* @Date:   2019-10-28 19:52:22
* @Last Modified by:   Administrator
* @Last Modified time: 2019-11-01 16:34:17
*/

/**
 * 邻接矩阵实现的map 
 */
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

#define  IS_LETTER(c)   ( (((c) >= 'a') && ((c) <= 'z')) || (((c) >= 'A') && ((c) <= 'Z')) )
#define  LENGTH(c)      (sizeof(c)/(sizeof(c[0])))

#define MAX_VERTEX (200)

// 临接矩阵结构体
typedef struct GRAPH
{
    int vertex_number;
    int edge_number;
    char vertex[MAX_VERTEX];
    int matrix[MAX_VERTEX][MAX_VERTEX];

}Graph, *P_Graph;


char get_letter()
{
    char ch;

    ch = getchar();
    while(!IS_LETTER(ch)) 
    {
        ch = getchar();
    }

    return ch;
}


int get_position(Graph graph, char ch)
{
    for (int i = 0; i < graph.vertex_number; ++i)
    {
        if (graph.vertex[i] == ch)
        {
            return i;
        }
    }

    return -1;
}

Graph *create_graph()
{   
    char c1, c2;
    int pos1, pos2;
    int vertex, edge;

    Graph *p_graph = NULL;

    printf("输入顶点数量：");
    scanf("%d", &vertex);
    printf("输入边的数量：");
    scanf("%d", &edge);

    if (vertex < 1 || edge < 1 || (edge > (vertex*(vertex-1))))
    {
        printf("输入参数有误，不符合图的要求！\n");
        return NULL;
    }

    p_graph = (Graph *)malloc(sizeof(Graph));
    if (NULL == p_graph)
    {
        return NULL;
    }

    memset(p_graph, 0, sizeof(Graph));

    p_graph->vertex_number = vertex;
    p_graph->edge_number = edge;

    // 初始化顶点
    for (int i = 0; i < p_graph->vertex_number; ++i)
    {
        printf("顶点：[%d] ", i);
        p_graph->vertex[i] = get_letter();
    }


    // 初始化边
    for (int i = 0; i < p_graph->edge_number; ++i)
    {
        printf("边： %d", i);
        c1 = get_letter();
        c2 = get_letter();

        pos1 = get_position(*p_graph, c1);
        pos2 = get_position(*p_graph, c2);

        if (pos1 == -1 || pos2 == -1)
        {
            free(p_graph);
            return NULL;
        }

        p_graph->matrix[pos1][pos2] = 1;
        p_graph->matrix[pos2][pos1] = 1;
    }

    return p_graph;

}

/*
 * 创建图(用已提供的矩阵)
 */
Graph* create_graph_2(char *vertex, char edges[][2], int vlen, int elen)
{
    int i, p1, p2;
    Graph* pG;
    
    if ((pG=(Graph*)malloc(sizeof(Graph))) == NULL )
        return NULL;
    memset(pG, 0, sizeof(Graph));

    // 初始化"顶点数"和"边数"
    pG->vertex_number = vlen;
    pG->edge_number = elen;
    printf("顶点数量： %d  边数 :%d\n", vlen, elen);
    // 初始化"顶点"
    for (i = 0; i < pG->vertex_number; i++)
    {
        pG->vertex[i] = vertex[i];
    }

    // 初始化"边"
    for (i = 0; i < pG->edge_number; i++)
    {
        // 读取边的起始顶点和结束顶点
        p1 = get_position(*pG, edges[i][0]);
        p2 = get_position(*pG, edges[i][1]);

        // 如果是无向图，那么两个方向都设为1
        // 如果是有向图，则 pG->matrix[p1][p2] = 1;
        pG->matrix[p1][p2] = 1;
        pG->matrix[p2][p1] = 1;
    }

    return pG;
}

void print_graph(Graph graph)
{
    printf("顶点数量： %d\n", graph.vertex_number);

    for (int i = 0; i < graph.vertex_number; ++i)
    {
        for (int j = 0; j < graph.vertex_number; ++j)
        {
            printf("%d ", graph.matrix[i][j]);
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

    Graph* p_graph_2 = create_graph_2(vertex, edges, LENGTH(vertex), LENGTH(edges));
    print_graph(*p_graph_2);

    // Graph* p_graph = create_graph();
    // print_graph(*p_graph);

    return 0;
}