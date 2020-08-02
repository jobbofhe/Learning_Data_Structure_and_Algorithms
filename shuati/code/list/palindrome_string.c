/*
* @Author: shuqiang
* @Date:   2020-08-02 13:17:23
* @Last Modified by:   Administrator
* @Last Modified time: 2020-08-02 23:30:45
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
		// 不带头节点
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
	count++;

	return count;
}

/**
 * 不带头节点
 */
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

/**
 * 查找链表的中间节点.
 * 思路：
 * 1. 快指针每次前进两个节点，慢节点每次前进一个节点
 * 2. 如果快指针走到了末尾，或者快指针的下一个节点走到了末尾，停止
 * 3. 此时，慢指针指向的位置就是中间节点
 *
 * 说明：这里链表节点数有奇数和偶数之分，奇数不用考虑了。如果是偶数，则取上中位置
 * 例如：1 2 3 4 5 6
 * 中间节点为3
 */
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

List *local_reverse(List * head) 
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

/**
 * 判断链表是否是回文
 * 思路：
 * 1. 找到链表的中间节点
 * 2. 反转后半部分链表
 * 3. 重新便利原链表和反转之后的后半部分链表，一一比较数值
 * 4. 返回之前回复被逆转的链表
 */
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

#if 0

/**
 * 删除链表中倒数第 K 个点
 */
void delete_ordered_k_node(List *list, int k)
{
	if (!list || k <= 0)
	{
		return;
	}

	Node *head = list;
	if(head->next == NULL)
	{
		if (k == 1)
		{
			free(list);
			list = NULL;
			return;
		}
		else
		{
			return;
		}
	}

	int size = get_list_size(list);
	if (k > size)
	{
		printf("\nk [%d] 大于链表长度 [%d]\n", k, size);
		return ;
	}
	else if (k == 10)
	{
		printf("\n删除头节点\n");
		head = list->next;
		free(list);
		list = head;
	}
	else
	{
		Node *pSlow = list;
		Node *pFast = list;
		Node *pPre =  NULL;
		int count = 0;

		// 快指针向前到 k-1 位置
		while(count++ != (k-1)) 
		{
			pFast = pFast->next;
		}

		// 快 慢指针同时前进
		while(pFast->next) 
		{
			pPre = pSlow;
			pSlow = pSlow->next;
			pFast = pFast->next;
		}

		pPre->next = pSlow->next;
		pSlow->next = NULL;
		free(pSlow);
		pSlow = NULL;

		printf("\n倒数第 [%d] 个节点是：%d\n", k, pSlow->value);
	}
}

#endif 


/**
 * 删除链表中倒数第 K 个点
 */
void delete_ordered_k_node(List **list, int k)
{
	Node *head = *list;

	if (!head || k <= 0)
	{
		return;
	}

	if(head->next == NULL)
	{
		if (k == 1)
		{
			free(*list);
			*list = NULL;
			return;
		}
		else
		{
			return;
		}
	}

	int size = get_list_size(*list);
	if (k > size)
	{
		printf("\nk [%d] 大于链表长度 [%d]\n", k, size);
		return ;
	}
	else if (k == 10)
	{
		printf("\n删除头节点\n");
		head = (*list)->next;
		free(*list);
		*list = head;
	}
	else
	{
		Node *pSlow = head;
		Node *pFast = head;
		Node *pPre =  NULL;
		int count = 0;

		// 快指针向前到 k-1 位置
		while(count++ != (k-1)) 
		{
			pFast = pFast->next;
		}

		// 快 慢指针同时前进
		while(pFast->next) 
		{
			pPre = pSlow;
			pSlow = pSlow->next;
			pFast = pFast->next;
		}

		pPre->next = pSlow->next;
		pSlow->next = NULL;
		free(pSlow);
		pSlow = NULL;

		printf("\n倒数第 [%d] 个节点是：%d\n", k, pSlow->value);
	}
}

void test_delete_ordered_k_node(List **list)
{
	int k = 10;

	printf("\n删除第[%d]个结点之后：\n", k);
	delete_ordered_k_node(list, k);
	print_list(*list);

	int size = get_list_size(*list);
	printf("\nlist size: %d\n", size);

}

void test_find_mid_node(List *list)
{
	Node *mid = find_middle_node(list);
	printf("\nmid: %d\n", mid->value);
}

void test_is_palindrome(List *list)
{
	printf("\nIs palindrome?\n");
	bool flag = is_palindrome(list);
	if (flag)
	{
		printf("Yes\n");
	}
	else
	{
		printf("No\n");
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
	insertNodeToListTail(list, createNode(5));
	insertNodeToListTail(list, createNode(4));
	insertNodeToListTail(list, createNode(3));
	insertNodeToListTail(list, createNode(2));
	insertNodeToListTail(list, createNode(1));

	printf("src list: \n");
	print_list(list);

	// test 1: find middle mode in link
	test_find_mid_node(list);

	// test 2: is palinfrome
	test_is_palindrome(list);

	// test 3: delte reciprocal K node
	test_delete_ordered_k_node(&list);

	// 2. destroy list
	destroy_list(list);
	return 0;
}