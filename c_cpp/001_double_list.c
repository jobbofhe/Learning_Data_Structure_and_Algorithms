
// /**
//  * 双向链表
//  * 初始化链表 ： A B C D E F G H I J K L M N O P Q R S T U V W X Y
//  * 输入正整数4： E F G H I J K L M N O P Q R S T U V W X Y Z A B C D
//  * 输入负整数4： E F G H I J K L M N O P Q R S T U V W X Y Z A B C D
//  */
// #include <stdio.h>
// #include <stdlib.h>

// typedef char ElemType;
// typedef int Status;

// #define     TRUE    (1)
// #define     FALSE   (0)    

// typedef struct DoubleNode
// {
//     ElemType data;
//     struct DoubleNode *pre;
//     struct DoubleNode *next;

// }DoubleNode, *DoubleList;


// Status initList(DoubleList *list)
// {
//     // malloc header node
//     DoubleList pHead = (DoubleList)malloc(sizeof(DoubleNode));
//     DoubleNode *p, *q;

//     (*list) = pHead;
//     (*list)->pre = (*list)->next = NULL;
//     if(!(*list))
//     {
//         return FALSE;
//     }
//     p = (*list);

//     int i = 0;
//     for (i = 0; i < 26; i++)
//     {
//         q = (DoubleNode*)malloc(sizeof(DoubleNode));
//         if(!q)
//         {
//             return FALSE;
//         }
//         q->data = 'A' + i;
//         q->pre = p;
//         q->next = p->next;
//         p->next = q;
//         printf("%c ", p->data);
//         p = q;
//     }
//     // 循环完毕，为结点指向头结点的 next结点，头结点的next结点指尾结点
//     p->next = (*list)->next;
//     (*list)->next->pre = p;
//     printf("\n");

//     return TRUE;
// }

// void Sort(DoubleList *list, int i)
// {
//     if (i > 0)
//     {
//         printf("i > 0\n");
//         do
//         {
//             (*list) = (*list)->next;
//         }while(--i);
//     }
//     if (i < 0)
//     {
//         i = i+26;
//         printf("i < 0\n");
//         do 
//         {
//             (*list) = (*list)->next;
//         }while(--i);
//     }
// }

// void PrintList(DoubleList *list)
// {
//     if(!list)
//     {
//         return;
//     }
//     int i = 0;
//     for ( i = 0; i < 26; ++i)
//     {
//         (*list) = (*list)->next;
//         printf("%c ", (*list)->data);
//     }
// }

// int main(int argc, char const *argv[])
// {

//     DoubleList *list = (DoubleList*)malloc(sizeof(DoubleList));

//     initList(list);

//     int number;
//     printf("Please input an int number: ");
//     scanf("%d", &number);

//     printf("number [%d]\n", number);
//     Sort(list, number);

//     PrintList(list);

//     return 0;
// }


#include <stdio.h>
#include <stdlib.h>

typedef struct PEOPLE
{
    char *name;
    int age;

}People;

typedef struct Node_
{
    int value;

    struct Node_ *pre;
    struct Node_ *next;

}Node, *NodeList;


Node *create_node(int value)
{
    Node * p = (Node*)malloc(sizeof(Node));

    if (p == NULL)
    {
        return NULL;
    }

    p->pre = p->next = p;
    p->value = value;

    return p;
}

NodeList create_node_list()
{
    NodeList list = (NodeList)malloc(sizeof(Node));

    if (!list)
    {
        return NULL;
    }

    list->pre = list->next = list;
    list->value = -1;

    return list;
}

int list_is_empty(NodeList list)
{
    if (!list)
    {
        return -1;
    }

    if (list->pre == list->next)
    {
        // 链表为空
        return 0; 
    }

    return -1;
}

void print_list(NodeList list)
{   
    if (!list)
    {
        return;
    }

    int flag = list_is_empty(list);

    if (flag == 0)
    {
        printf("链表为空！\n");
        return;
    }

    list = list->next;

    while(list->value != -1) 
    {
        printf("--> : %d ", list->value);

        list = list->next;
    }

    printf("\n");
}

void insert_node_from_head(NodeList list, int value)
{
    Node * node = create_node(value);

    // 新的结点插入到头结点之后，头结点的下一个结点之前
    // 头结点的下一个结点首先指向 新结点
    list->next->pre = node;
    // 新结点的下一个结点指向头结点的下一个结点
    node->next = list->next;

    // 更新头结点的下一个结点
    list->next = node;
    node->pre = list;

    printf("头部插入： %d 完成。\n", value);
}

void insert_node_from_tail(NodeList list, int value)
{
    Node *node = create_node(value);

    // 循环到尾结点
    while(list->next->value != -1) 
    {
        list = list->next;
    }

    // 新结点的下一个结点指向头结点
    node->next = list->next;
    // 头结点指向新结点
    list->next = node;
    // 新结点的前去指向原来的最后一个节点
    node->pre = list;   

    printf("尾部插入： %d 完成。\n", value);
}

int delete_node_by_value(NodeList list, int value)
{   
    list = list->next;

    NodeList pre, next, del_node;

    while(list->value != -1) 
    {
        if (list->value == value)
        {
            del_node = list;

            pre = list->pre;
            next = list->next;

            next->pre = pre;
            pre->next = next;

            printf("删除成功！\n");
            return 0;
        }

        list = list->next;
    }
    printf("数据为[%d]的元素不存在！\n", value);
    return -1;
}

// 在当前节点之后插入新的节点
int insert_node_from_pos(NodeList list, int pos, int value)
{
    if (NULL == list)
    {
        return -1;
    }

    Node * node = create_node(value);

    list = list->next;
    NodeList current_node = NULL;

    while(list->value != -1) 
    {
        if (list->value == pos)
        {
            printf("找到了数据为[%d]的节点。\n", value);
            current_node = list;

            node->pre = current_node;
            current_node->next->pre = node;
            node->next = current_node->next;
            current_node->next = node;

            printf("在节点 [%d]后插入新节点[%d]\n", pos, value);

            return 0;
        }
        list = list->next;
    }
}

// 找到值为value的节点，将其值修改未value2
int set_value_at_pos(NodeList list, int pos, int value)
{
    if (NULL == list)
    {
        return -1;
    }

    list = list->next;

    while(list->value != -1) 
    {
        if (list->value == pos)
        {
            list->value = value;

            printf("将结点为 [%d] 的值修改为 [%d].\n", pos, value);
            return 0;
        }

        list = list->next;
    }

    printf("数据为[%d]的元素不存在！\n", value);
    return -1;
}


int main(int argc, char const *argv[])
{
    NodeList list = create_node_list();
    insert_node_from_head(list, -1);

    int i = 0;
    for (i; i < 5; i++)
    {
        insert_node_from_head(list, i*2);

        insert_node_from_tail(list, i*3);
    }

    print_list(list);

    delete_node_by_value(list, 0);

    print_list(list);

    insert_node_from_pos(list, 9, 999);
    print_list(list);

    set_value_at_pos(list, 999, 123456);
    print_list(list);


    return 0;
}
