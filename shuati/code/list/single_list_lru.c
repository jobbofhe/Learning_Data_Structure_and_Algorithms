/*
* @Author: shuqiang
* @Date:   2020-08-01 17:14:36
* @Last Modified by:   Administrator
* @Last Modified time: 2020-08-07 20:38:38
*/


/**
 * LRU：Least Recently Used
 * 基于单链表实现LRU缓存淘汰算法
 * 思路：
 * 遍历链表
 * 	如果节点已存在，则删已存在的节点，然后将新节点插入链表头部
 * 		这里因该有判断 是否找到的节点就是头节点
 * 	如果节点不存存在，判断链表缓存是否满了，
 * 		如果满了，删除最后一个节点，将新节点插入链表头部
 * 		如果未满，直接插入头部
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

const int LIST_MAX_SIZE = 8;

typedef struct Node_
{
	int 		 value;
	struct Node_ *next;

}Node, List;

int insertNodeToListHead(List **pList, Node *node)
{
	if (!node)
	{
		return -1;
	}

	if (!pList)
	{
		*pList = node;
	}
	else
	{
		node->next = *pList;
		*pList = node;		
	}	

	return 0;
}

Node *createNode(int value)
{
	Node *node = (Node *)malloc(sizeof(Node));
	if (node)
	{

		node->value = value;

		node->next = NULL;
	}
	else
	{
		return NULL;
	}

	return node;	
}

List *createList()
{
	List * list = (List*)malloc(sizeof(List));

	list->value =-1;
	list->next = NULL;

	return list;
}

int node_is_exit(List *list, Node *node)
{
	if (!list)
	{
		return -1;
	}

	List *p = list;

	while(p->next) 
	{
		if (p->value == node->value)
		{
			return 0;
		}

		p = p->next;
	}

	return -1;
}

/**
 * 删除已存在的节点
 */
int delete_node(List **list, Node *node)
{
	if(!list)
	{
		return -1;
	}

	Node *p1 = NULL, *p2 = NULL;

	p1 = *list;

	while(p1->next) {
		if (node->value == p1->value)
		{
			break;
		}
		else
		{
			p2 = p1;
			p1 = p1->next;
		}
	}

	// 如果要删除的节点就是头节点
	if (p1 == *list)
	{
		*list = p1->next;
		free(p1);
		p1 = NULL;
	}
	else
	{
		p2->next = p1->next;
		free(p1);
		p1 = NULL;
	}

	return 0;
}

/**
 * 删除尾节点
 */

void delete_tail_node(List **list)
{
	if (*list)
	{
		List *p = *list;
		List *p_before = NULL;

		while(p->next) 
		{
			p_before = p;
			p = p->next;
		}

		free(p);
		p = NULL;
		p_before->next = NULL;
	}
}


void print_list(List *pList)
{
	if (!pList)
	{
		return;
	}

	List *p = pList;
	while(p->next) 
	{
		printf("%d ", p->value);

		p = p->next;
	}

	printf("\n");
}

int get_list_size(List *list)
{
	if (!list)
	{
		return 0;
	}

	int count = 0;

	List *p = list;
	while(p->next) 
	{
		count++;
		p = p->next;
	}

	return count;
}


int main(int argc, char const *argv[])
{
	List *list = createList();

	Node *node = createNode(100);
	insertNodeToListHead(&list, node);
	insertNodeToListHead(&list, createNode(1));
	insertNodeToListHead(&list, createNode(5));
	insertNodeToListHead(&list, createNode(6));
	insertNodeToListHead(&list, createNode(9));
	insertNodeToListHead(&list, createNode(20));
	insertNodeToListHead(&list, createNode(30));
	insertNodeToListHead(&list, createNode(99));

	print_list(list);

	// new
	node = createNode(20);

	// 缓存区没有满
	if (LIST_MAX_SIZE < get_list_size(list))
	{
		if (0 == node_is_exit(list, node))
		{
			// delete old node
			delete_node(&list, node);

			// insert new node
			insertNodeToListHead(&list, node);
		}
	}
	else // 缓存区已满
	{
		delete_tail_node(&list);
		insertNodeToListHead(&list, node);
	}
	

	print_list(list);

	return 0;
}