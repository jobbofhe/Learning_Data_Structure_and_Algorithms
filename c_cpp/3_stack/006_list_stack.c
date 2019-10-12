/*
* @Author: jobbofhe
* @Date:   2019-07-20 15:25:46
* @Last Modified by:   Administrator
* @Last Modified time: 2019-07-26 15:09:35
*/

#include <stdio.h>
#include <malloc.h>


typedef struct node_
{
    int value;
    struct node_ *next;

}node;

static node *phead = NULL;

node *create_node(int value)
{
    node *pnode = (node*)malloc(sizeof(node));

    if (NULL == pnode)
    {
        printf("Failed to create node!\n");
        return NULL;
    }

    pnode->value = value;
    pnode->next = NULL;
}

void destroy_list_stack()
{
    node *pnode = phead;

    while(phead != NULL) 
    {
        pnode = phead;
        phead = phead->next;
        free(pnode);
    }
}

// 新节点插入到头结点之前
int push_list_stack(int value)
{
    node *pnode = create_node(value);

    pnode->next = phead;
    phead = pnode;
}

// 出栈，头结点的指向的元素出栈并释放
int pop_list_stack()
{
    if(NULL == phead)
    {
        printf("Head node is null!\n");
        return -1;
    }
    node *pnode = NULL;

    int ret = phead->value;
    pnode = phead;
    phead = phead->next;

    free(pnode);

    return  ret;
}

// 返回栈顶元素
int peek_list_stack()
{
    if(NULL == phead)
    {
        printf("Head node is null!\n");
        return -1;
    }

    return phead->value;
}

int size_list_stack()
{
    int count = 0;
    node *pnode = phead;

    while(pnode != NULL) 
    {
        pnode = pnode->next;
        count++;
    }

    return count;
}

int is_empty()
{
    return phead == NULL;
}

void printf_stack()
{
    if (is_empty())
    {
        printf("Stack is NULL!\n");
        return;
    }

    printf("Stack size: %d\n", size_list_stack());

    node *pnode = phead;

    while(pnode != NULL) 
    {
        printf("%d\n", pnode->value);
        pnode = pnode->next;
    }
}

// 函数中不可对头指针进行操作
int main(int argc, char const *argv[])
{
    
    int i = 0;
    for (i = 0; i < 5; ++i)
    {
        push_list_stack(i*3);
    }

    printf_stack();

    for (i = 0; i < 3; ++i)
    {
        pop_list_stack();
    }
    printf_stack();

    return 0;
}