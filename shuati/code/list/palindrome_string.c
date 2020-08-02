/*
* @Author: shuqiang
* @Date:   2020-08-02 13:17:23
* @Last Modified by:   Administrator
* @Last Modified time: 2020-08-02 17:09:02
*/

/**
 * 题目要求：
 * 使用链表存储字符串，并且判断这个字符串是否是回文串
 *
 * 思路：
 * 1. 创建字符串的链表
 * 2. 快慢指针同时遍历链表，快指针每次前进两步，满指针每次前进一步，找到链表中点
 * 3. 反转后半部分链表
 * 4. 重新遍历链表，比较是否相等
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

int insertNodeToListTail(List *pList, Node *node)
{
	if (!node)
	{
		return -1;
	}

	if (!pList)
	{
		return -1;
	}
	else
	{
		while(pList->next) {
			
			pList = pList->next;
		}

		pList->next = node;		
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

	list->value = 1;
	list->next = NULL;

	return list;
}

void print_list(List *pList)
{
	if (!pList)
	{
		return;
	}

	List *p = pList;
	while(p) 
	{
		printf("%d ", p->value);

		p = p->next;
	}

	printf("\n");
}

Node *find_middle_node(List *list)
{
	Node *pFast = NULL, *pSlow = NULL;

	pFast = pSlow = list;

	while(pFast->next && pFast->next->next) 
	{
		pFast = pFast->next->next;
		pSlow = pSlow->next;
	}

	return pSlow;
}

List * local_reverse(List * head) 
{
    List * beg = NULL;
    List * end = NULL;
    if (head == NULL || head->next == NULL) 
    {
        return head;
    }
    beg = head;
    end = head->next;
    while (end != NULL) 
    {
        //将 end 从链表中摘除
        beg->next = end->next;
        //将 end 移动至链表头
        end->next = head;
        head = end;
        //调整 end 的指向，另其指向 beg 后的一个节点，为反转下一个节点做准备
        end = beg->next;
    }
    return head;
}

List * reverse_list(List *list)
{
	Node *pCur = NULL;
	Node *pNext;

	while(list)
	{
		pNext = list->next;
		list->next = pCur;
		pCur = list;
		list = pNext;
	}

	return pCur;
}

List * reverse_list_2(List *list)
{
	Node *pPre = list;
	Node *pCur = list->next;
	Node *pNext;// = list->next->next;

	while(pCur) 
	{
		// 记录下一个节点
		pNext = pCur->next;
		// 当前节点向后移动
		pCur->next = pPre;
		// 前一个节点，向后移动到当前节点
		pPre = pCur;
		// 当前节点，向后移动到下一个节点
		pCur = pNext;
	}
	// 循环结束之后，头节点被移动到了为节点，需要将头节点的next置空
	list->next = NULL;

	return pPre;
}

/**
 * 递归实现单链表反转
 */
List * reverse_list_3(List *list)
{
	// 递归结束条件
	// 如果头节点为空递归结束，或者头节点的next节点为空，说明反转完成，递归结束
	if(!list || !(list->next))
	{
		return list;
	}
	else
	{
		// 递归到链表的最后两个开始操作
		Node *newHead = reverse_list_3(list->next);
		// 将后一个节点指向前一个节点
		list->next->next = list;
		// 将原链表中前一个节点执行后一个节点的next 断开
		list->next = NULL;
		return newHead;
	}
}


bool is_palindrome(List *list)
{
	Node *pHead = list;
	Node *pMid = find_middle_node(list);
	
	Node *pRever = reverse_list_2(pMid->next);
	Node *pReverHead = pRever;

	while(pReverHead) 
	{
		if (pReverHead->value != pHead->value)
		{
			pReverHead = reverse_list_2(pReverHead);
			pMid->next = pReverHead;

			return false;
		}

		pReverHead = pReverHead->next;
		pHead = pHead->next;
	}

	// 恢复反转
	pRever = reverse_list_2(pRever);
	pMid->next = pRever;

	return true;
}

void destroy_list(List *list)
{
	if (list)
	{
		Node *p = NULL, *q = NULL;

		p = list;
		while(p) 
		{
			q = p->next;
			free(p);
			p = q;
		}
	}
}

int main(int argc, char const *argv[])
{
	// 1. create list
	List *pHead = NULL;
	List *list = createList();
	insertNodeToListTail(list, createNode(2));
	insertNodeToListTail(list, createNode(3));
	insertNodeToListTail(list, createNode(4));
	insertNodeToListTail(list, createNode(5));
	insertNodeToListTail(list, createNode(4));
	insertNodeToListTail(list, createNode(3));
	insertNodeToListTail(list, createNode(2));
	insertNodeToListTail(list, createNode(10));

	print_list(list);

	// 2. judge palindrome

	printf("Is palindrome?\n");
	bool flag = is_palindrome(list);
	if (flag)
	{
		printf("Yes\n");
	}
	else
	{
		printf("No\n");
	}

	// 3. destroy list
	destroy_list(list);
	return 0;
}