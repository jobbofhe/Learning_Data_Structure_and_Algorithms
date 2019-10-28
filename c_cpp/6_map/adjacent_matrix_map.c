/*
* @Author: jobbofhe
* @Date:   2019-10-28 19:52:22
* @Last Modified by:   Administrator
* @Last Modified time: 2019-10-28 20:37:56
*/

#include <stdio.h>
#include <stdlib.h>

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

void print_graph(Graph graph)
{
    printf("顶点数量： %d\n", graph.vertex_number);

    for (int i = 0; i < graph.vertex_number; ++i)
    {
        for (int j = 0; j < graph.vertex_number; ++i)
        {
            printf("%d ", graph.matrix[i][j]);
        }
        printf("\n");
    }
}

int main(int argc, char const *argv[])
{
    /* code */

    Graph* p_graph = create_graph();

    print_graph(*p_graph);

    return 0;
}