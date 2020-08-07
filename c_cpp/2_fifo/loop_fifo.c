/*
* @Author: shuqiang
* @Date:   2020-08-07 20:14:16
* @Last Modified by:   Administrator
* @Last Modified time: 2020-08-07 21:27:33
*/

/**
 * 循环队列
 * 为什么要使用循环队列：减少顺序队列空间的浪费
 *
 * 牺牲一个元素空间，约定以“队列头指针在队列尾指针的下一位置（指环状的下一位置）上”。
 *
 * 头指针：front
 * 尾指针：rear
 * 
 * 初始化：front = rear = 0
 *
 * 入队：rear++
 * 出队：front++
 * 
 * 队空的判断：头指针等于尾指针
 * 队满的判断：(尾指针+1) % 队列大小 == 头指针
 * 
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


typedef struct QueueElem_
{
	int *data;
	int front;
	int rear;
	int size;

}QueueElem;

bool create_loop_queue(QueueElem *pQueue, int queueSize)
{
	pQueue->data = (int*)malloc(sizeof(int)*queueSize);
	if (NULL == pQueue->data)
	{
		return false;
	}

	pQueue->front = pQueue->rear = 0;
	pQueue->size = queueSize;

	return true;
}

bool loop_queue_is_empty(QueueElem *pQueue)
{
	return pQueue->front == pQueue->rear;
}

bool loop_queue_is_full(QueueElem *pQueue)
{
	return (pQueue->rear+1)%pQueue->size == pQueue->front;
}

bool enQueue(QueueElem *pQueue, int data)
{
	if (loop_queue_is_full(pQueue))
	{
		printf("loop queue is full.\n");
		return false;
	}

	pQueue->data[pQueue->rear] = data;
	pQueue->rear = (pQueue->rear+1)%pQueue->size;

	return true;
}

bool deQueue(QueueElem *pQueue)
{
	if (loop_queue_is_empty(pQueue))
	{
		printf("loop queue is empty.\n");
		return false;
	}
	if (pQueue->front == pQueue->rear)
	{
		pQueue->front = 0;
		pQueue->rear = 0;

		return true;
	}

	pQueue->front = (pQueue->front+1) % pQueue->size;

	return true;
}

int get_head_elem(QueueElem *pQueue)
{
	if (loop_queue_is_empty(pQueue))
	{
		return -1;
	}

	return pQueue->data[pQueue->front];
}

int get_tail_elem(QueueElem *pQueue)
{
	if (loop_queue_is_empty(pQueue))
	{
		return -1;
	}

	return pQueue->data[pQueue->rear];
}

int get_queue_size(QueueElem *pQueue)
{
	if (loop_queue_is_empty(pQueue))
	{
		return 0;
	}

	if (pQueue->front < pQueue->rear)
	{
		return pQueue->rear - pQueue->front + 1;
	}
	else if (pQueue->front == pQueue->rear)
	{
		return 1;
	}
	else
	{
		return (pQueue->front + pQueue->rear + 1)%pQueue->size;
	}
}

void show_queue(QueueElem *pQueue)
{
	if (loop_queue_is_empty(pQueue))
	{
		printf("loop queue is empty.\n");
		return;
	}

	if (pQueue->front < pQueue->rear)
	{
		for (int i = pQueue->front; i < pQueue->rear; ++i)
		{
			printf("%d ", pQueue->data[i]);
		}
		printf("\n");
	}
	else if (pQueue->front > pQueue->rear)
	{
		for (int i = pQueue->front; i < pQueue->size; ++i)
		{
			printf("%d ", pQueue->data[i]);
		}
		for (int i = 0; i < pQueue->rear; ++i)
		{
			printf("%d ", pQueue->data[i]);
		}
		printf("\n");
	}
	else
	{
		printf("%d ", pQueue->data[pQueue->front]);
	}
}

void destroy_queue(QueueElem *pQueue)
{
	if (pQueue)
	{
		if (pQueue->data)
		{
			free(pQueue->data);
		}
		pQueue->size = 0;
	}
}

int main(int argc, char const *argv[])
{

	QueueElem stQueue = {};

	create_loop_queue(&stQueue, 10);

	for (int i = 0; i < 15; ++i)
	{
		enQueue(&stQueue, i);
	}

	for (int i = 0; i < 5; ++i)
	{
		deQueue(&stQueue);
	}

	
	show_queue(&stQueue);
	destroy_queue(&stQueue);

	return 0;
}