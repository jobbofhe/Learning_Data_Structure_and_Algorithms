/*
* @Author: jobbofhe
* @Date:   2019-11-06 17:38:21
* @Last Modified by:   Administrator
* @Last Modified time: 2019-11-06 19:57:57
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

/*
 * 创建图(用已提供的图数据)
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

/**
 * 获取第一个临接点的索引
 * @param  graph     [description]
 * @param  index_first [description]
 * @return           [description]
 */
int get_vertex_first_index(Graph graph, int index_first)
{
	if (index_first < 0 || index_first > (graph.vertex_number-1))
	{
		return -1;
	}

	for (int i = 0; i < graph.vertex_number; ++i)
	{
		// 如果临接矩阵 中顶点 index_vex的连接点 存在，则返回邻接点的索引
		if (graph.matrix[index_first][i] == 1)
		{
			return i;
		}
	}

	return -1;
}

/**
 * 获取下一个临接点的索引
 * @param  graph      [description]
 * @param  index_first[description]
 * @param  index_next [description]
 * @return            [description]
 */
int get_vertex_next_index(Graph graph, int index_first, int index_next)
{
	if (index_first < 0 || index_first > (graph.vertex_number-1) 
		|| index_next < 0 || index_next >(graph.vertex_number-1))
	{
		return -1;
	}

	for (int i = index_next+1; i < graph.vertex_number; ++i)
	{
		if (graph.matrix[index_first][i] == 1)
		{
			return i;
		}
	}

}

void DFS(Graph graph, int index, int *flag_visited)
{
	flag_visited[index] = 1;

	printf("%c ", graph.vertex[index]);

	int i = 0;

	// 遍历该顶点的所有邻接点,如果访问数组标记位为0，则继续访问
	for (i = get_vertex_first_index(graph, index); i >= 0; i = get_vertex_next_index(graph, index, i))
	{
		if (flag_visited[i] == 0)
		{
			DFS(graph, i, flag_visited);
		}
	}
}

/**
 * 深度优先搜索遍历图
 * @param graph [graph]
 */
void deep_first_search(Graph graph)
{
	// 节点被访问标记
	int flag_visited[MAX_VERTEX];
	for (int i = 0; i < graph.vertex_number; ++i)
	{
		// 访问之前所有顶点被访问标记置为0
		flag_visited[i] = 0;
	}
	printf("------------ DFS -------------\n");
	for (int i = 0; i < graph.vertex_number; ++i)
	{
		if (flag_visited[i] == 0)
		{
			DFS(graph, i, flag_visited);
		}
	}

	printf("\n");
}

/**
 * 广度优先遍历图
 */
void breadth_first_search(Graph graph)
{
	int tmp_array[MAX_VERTEX];
	// 节点被访问标记
	int flag_visited[MAX_VERTEX];
	for (int i = 0; i < graph.vertex_number; ++i)
	{
		// 访问之前所有顶点被访问标记置为0
		flag_visited[i] = 0;
	}

	printf("---------- BFS ----------\n");

	int head = 0;
	int tail = 0;
	for (int i = 0; i < graph.vertex_number; ++i)
	{
		if (flag_visited[i] == 0)
		{
			flag_visited[i] = 1;
			printf("%c ", graph.vertex[i]);
			tmp_array[tail++] = i; // 已经访问过的写入临时数组
		}

		while(head != tail) 
		{
			int j = tmp_array[head++]; // 将已经访问过的节点取出来
			for (int k = get_vertex_first_index(graph, j); k > 0; k = get_vertex_next_index(graph, j, k))
			{
				if (flag_visited[k] == 0)
				{
					flag_visited[k] = 1;
					printf("%c ", graph.vertex[k]);
					tmp_array[tail++] = k;
				}
			}
			
		}
	}
	printf("\n");
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

    deep_first_search(*p_graph_2);

    breadth_first_search(*p_graph_2);

    return 0;
}