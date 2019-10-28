/*
* @Author: jobbofhe
* @Date:   2019-10-28 19:52:22
* @Last Modified by:   Administrator
* @Last Modified time: 2019-10-28 20:12:13
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

Graph *create_graph()
{   
    
}

void printf_graph(Graph graph)
{

}

int main(int argc, char const *argv[])
{
    /* code */
    return 0;
}