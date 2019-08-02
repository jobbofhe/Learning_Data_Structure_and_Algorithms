/*
* @Author: jobbofhe
* @Date:   2019-07-26 17:23:47
* @Last Modified by:   Administrator
* @Last Modified time: 2019-07-29 19:18:24
*/

#include <stdio.h>
#include <malloc.h>

// #include <006_double_list_stack.h>

// 双链表接口封装
typedef struct d_node
{
    void *p;
    struct d_node *pre;
    struct d_node *next;

}node;

// 头结点，不存放元素
// static node *phead = NULL;
static int count = 0;

node *create_node(void *pvalue)
{
    node *pnode = (node*)malloc(sizeof(node));
    if (NULL == pnode)
    {
        return NULL;
    }

    pnode->pre = pnode->next = pnode;
    pnode->p = pvalue;

    return pnode;
}

node *create_double_list()
{
    node *plist = create_node(NULL);

    if (NULL == plist)
    {
        printf("Failed to create double list.");
        return NULL;
    }

    count = 0;

    return plist;
}

int double_list_is_empty()
{
    return count == 0;
}

int double_list_size()
{
    return count;
}

node *get_node_by_index(node *plist, int index)
{
    if (double_list_is_empty())
    {
        printf("[%s] Double list is empty!\n", __func__);
        return NULL;
    }

    if (index < 0 || index >= count)
    {
        printf("%s failed! index out of bound!\n", __func__);
        return NULL;
    }

    node *pnode = NULL;

    // 正向查找
    if(index <= count/2)
    {
        int i = 0;

        pnode=plist->next;
        while((i++) < index) 
        {
            pnode = pnode->next;
        }

        return pnode;
    }

    // 反向查找
    int j = 0;
    int lindex = count - index - 1;
    pnode = plist->pre;

    while((j++) < lindex) 
    {
        pnode = pnode->pre;
    }

    return pnode;
}

node *get_first_node(node *plist)
{
    if (double_list_is_empty())
    {
        printf("[%s] Double list is empty!\n", __func__);
        return NULL;
    }

   node *pnode = get_node_by_index(plist, 0);
   
   return pnode;
}

node *get_last_node(node *plist)
{
    if (double_list_is_empty())
    {
        printf("[%s] Double list is empty!\n", __func__);
        return NULL;
    }

   node *pnode = get_node_by_index(plist, count - 1);
   
   return pnode;
}

void *get_value_by_index(node *plist, int index)
{
    if (double_list_is_empty())
    {
        printf("[%s] Double list is empty!\n", __func__);
        return NULL;
    }

    node *pnode = get_node_by_index(plist, index);

    return pnode->p;
}

void *get_first_value(node *plist)
{
    if (double_list_is_empty())
    {
        printf("[%s] Double list is empty!\n", __func__);
        return NULL;
    }

    return get_value_by_index(plist, 0);
}

void *get_last_value(node *plist)
{
    if (double_list_is_empty())
    {
        printf("[%s] Double list is empty!\n", __func__);
        return NULL;
    }

    return get_value_by_index(plist, count - 1);
}

int insert_value_to_first(node *plist, void *pvalue)
{
    node *pnode = create_node(pvalue);

    if (NULL == pnode)
    {
        return -1;
    }

    pnode->pre = plist;
    pnode->next = plist->next;
    plist->next->pre = pnode;
    plist->next = pnode;

    count++;

    return 0;
}

// 将value值插入到 index 节点之前
int insert_value_to_index(node *plist, void *pvalue, int index)
{
    if (double_list_is_empty())
    {
        printf("[%s] Double list is empty!\n", __func__);
        return -1;
    }

    if (index == 0)
    {
        return insert_value_to_first(plist, pvalue);
    }

    node *pnode = get_node_by_index(plist, index);
    if (NULL == pnode)
    {
        return -1;
    }

    node *pnew = create_node(pvalue);
    if (NULL == pnew)
    {
        return -1;
    }

    pnew->pre = pnode->pre;
    pnew->next = pnode;
    pnode->pre->next = pnew;
    pnode->pre = pnode;

    count++;
    return 0;
}

int append_value_to_tail(node *plist, void *pvalue)
{
    node *pnew = create_node(pvalue);
    if (NULL == pnew)
    {
        return -1;
    }

    pnew->pre = plist;
    pnew->next = plist->pre;
    plist->pre->next = pnew;
    plist->pre = pnew;

    count++;

    return 0;
}

int delete_node_from_index(node *plist, int index)
{
    node *pindex = get_node_by_index(plist, index);

    if (NULL == pindex)
    {
        printf("%s failed! the index in out of bound!\n", __func__);
        return -1;
    }

    pindex->next->pre = pindex->pre;
    pindex->pre->next = pindex->next;
    free(pindex);
    count--;

    return 0;
}

int delete_first_node(node *plist)
{
    return delete_node_from_index(plist, 0);
}

int delete_last_node(node *plist)
{
    return delete_node_from_index(plist, count-1);
}

int destroy_double_list(node *plist)
{
    if (double_list_is_empty())
    {
        printf("[%s] Double list is empty!\n", __func__);
        return -1;
    }

    node *pnode = plist->next;
    node *p = NULL;

    while(plist != pnode) 
    {
        p = pnode->next;
        pnode = pnode->next;
        free(p);
    }

    free(plist);
}

// 双链表栈封装

node *create_double_list_stack()
{
    return create_double_list();
}

int destroy_double_list_stack(node *plist)
{
    return destroy_double_list(plist);
}

int push(node *plist, void *pvalue)
{
    return insert_value_to_first(plist, pvalue);
}

void* peek(node *plist)
{
    return get_first_value(plist);
}

void *pop(node *plist)
{
    void *p = peek(plist);

    delete_first_node(plist);

    return p;
}


int stack_size()
{
    return double_list_size();
}

int stack_is_empty()
{
    return double_list_is_empty();
}


typedef struct people 
{
    int age;
    char name[128];

}people;

void print(people *per)
{
    printf("%s : %d\n", per->name, per->age);
}

int main(int argc, char const *argv[])
{
    int i = 0;

    people *per = (people *)malloc(sizeof(people) * 10);

    for (i = 0; i < 5; ++i)
    {
        per[i].age = i*2;
        sprintf(per[i].name, "%s%d", "Test-", i);
    }

    node *pstack = create_double_list_stack();

    for (i = 0; i < 5; i++)
    {
        push(pstack, &(per[i]));
    }

    while(!stack_is_empty())
    {
        people * info = pop(pstack);
        print(info);
    }
    
    destroy_double_list(pstack);

    return 0;
}
