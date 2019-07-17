
#include<stdio.h>
#include<stdlib.h>
#define datatype int 
 
struct NODE
{
    int num;
    datatype data;       //存储数据
    struct NODE *pNext;
};
 
typedef struct NODE Node; //简写
 
//实现的功能  
//增加， 删除 ，查询 修改 排序 逆序 
 
void backAddNode(Node **ppNode, int num, datatype data);  //增加节点
Node *backAddNodeA(Node *pNode, int num, datatype data);  //增加节点 ，不使用二级指针，使用返回值
 
void showAllNode(Node *pNode);  //显示所有数据
Node *searchFirst(Node *pNode, int num); //查找
int change(Node *pNode, int oldNum, int newNum); //修改成功返回1，失败返回0
Node *reLink(Node *pNode);  //链表逆转
Node *deleteNode(Node *pNode, int num);//删除节点
void deleteNodeA(Node **ppNode, int num); //使用二级指针
Node *insertNode(Node *pNode, int findNum, int newNum, datatype data);
 
void sortLink(Node *pNode, char ch);
//ch == '>' ch == '<'
 
 
Node *backAddNodeA(Node *pNode, int num, datatype data)  //增加节点
{
    Node *pNewNode = (Node *)malloc(sizeof(Node));
    pNewNode->num = num;  //赋值
    pNewNode->data = data;  //赋值
    pNewNode->pNext = NULL;
     
    if (pNode == NULL) //传递过来的链表没有任何元素
    {
        //则让链表头指针等于pNewNode的值
        //让头指针指向pNewNode
        pNode = pNewNode;  //存储新点地址
        pNewNode->pNext = NULL;
    }
    else  //原链表有数据，则循环到链表末尾，在尾部插入数据
    {
        Node *p = pNode;  //头结点保存
         
         
        while (p->pNext != NULL)
        {
            p = p->pNext; //一直循环到结尾
        }

        p->pNext = pNewNode; //尾插
    }
    return pNode;
}
 
 
void backAddNode(Node **ppNode, int num, datatype data)
{
    Node *pNewNode = (Node *)malloc(sizeof(Node));
    pNewNode->num = num;  //赋值
    pNewNode->data = data;  //赋值
    pNewNode->pNext = NULL;
     
     
    if (*ppNode == NULL) //传递过来的链表没有任何元素
    {
        //则让链表头指针等于pNewNode的值
        //让头指针指向pNewNode
        *ppNode = pNewNode;  //存储新点地址
        pNewNode->pNext = NULL;
    }
    else  //愿链表有数据，则循环到链表末尾，在尾部插入数据
    {
        Node *p = *ppNode;  //头结点保存
         
         
        while (p->pNext != NULL)
        {
            p = p->pNext; //一直循环到结尾
        }
        p->pNext = pNewNode; //尾插
    }
     
     
}
void showAllNode(Node *pNode)  //显示所有数据
{
    printf("\n打印链表——:\n");
    while (pNode != NULL)
    {
        printf("%p, %p ", pNode, pNode->pNext);
        printf("%d, %d\n", pNode->num, pNode->data);
        pNode = pNode->pNext;
    }
}
 
 
Node *searchFirst(Node *pNode, int num)
{
    for (Node *p = pNode; p; p = p->pNext)
    {
        if (num == p->num)
        {
            return p;
            break;
        }
    }
    return NULL;
}
 
 
int change(Node *pNode, int oldNum, int newNum)
{
    //goto实现
    /*A: if (pNode != NULL)
    {
        if (oldNum == pNode->num) //找到oldNum.
        {
        pNode->num = newNum;
        return 1; // 改变成功，函数结束
        }
        pNode = pNode->pNext;  //否则pNode向后移动，继续查找
        goto A;
    }
   return 0;
*/
 
 
    //while实现
    /*while (pNode)
    {
        if (oldNum == pNode->num)
        {
            pNode->num = newNum;
            return 1;
        }
        pNode = pNode->pNext;
    }
    return 0;*/
 
 
    for (; pNode; pNode = pNode->pNext)
    {
        if (oldNum == pNode->num)
        {
            pNode->num = newNum;
            return 1;
        }
    }
 
   return 0;
}
 
Node *reLink(Node *pNode) //逆转链表
{
    Node *p1, *p2, *p3;
    p1 = p2 = p3 = NULL;
     
    //没有节点或只有一个节点
    if (pNode == NULL || pNode->pNext == NULL)
    {
        return pNode; //返回节点
    }
    else
    {
        p1 = pNode;
        p2 = pNode->pNext;
        while (p2 != NULL) //p2 = NULL时，链表遍历完成
        {
            p3 = p2->pNext;
            p2->pNext = p1; //转向
            p1 = p2;
            p2 = p3; //循环向前移动
        }
        pNode->pNext = NULL;
        //原来的头结点现在是末节点，为空
        pNode = p1;
        return pNode;
    }
}
 
//删除节点
Node *deleteNode(Node *pNode, int num)
{
    Node *p1 = NULL, *p2 = NULL;
    p1 = pNode;
          
    while (p1!= NULL) //找到要删除的点
    {
        if (num == p1->num)
        {
            //p1保存要删除节点的地址，找到了
             
             
            break;
        }
        else  //否则继续找
        {
            p2 = p1; //p2保存上一个节点
            p1 = p1->pNext; //向前循环
        }
    }
    if (p1 == pNode) //如果要删除的节点是头结点
    {
        pNode = p1->pNext; //跳过这个节点
        free(p1);  //删除节点
    }
    else
    {
        p2->pNext = p1->pNext;
        free(p1);
    }
    return pNode;
}
 
void deleteNodeA(Node **ppNode, int num)
{
    Node *p1 = NULL, *p2 = NULL;
    p1 = *ppNode;
     
     
    while (p1 != NULL) //找到要删除的点
    {
        if (num == p1->num)
        {
            //p1保存要删除节点的地址，找到了
            break;
        }
        else  //否则继续找
        {
            p2 = p1; //p2保存上一个节点
            p1 = p1->pNext; //向前循环
        }
    }
    if (p1 == *ppNode) //如果要删除的节点是头结点
    {
        *ppNode = p1->pNext; //跳过这个节点
        free(p1);  //删除节点
        p1 = NULL;
    } 
    //else和下边的注释相同结果
    else 
    {
        p2->pNext = p1->pNext;
        free(p1);
        p1 = NULL;   //防止出现野指针
    }
 
    /*else if (p1->pNext != NULL)
    {
        p2->pNext = p1->pNext;
        free(p1);
    }
    else  //最后一个节点的删除，p2->pNext = p1->pNext;
    //此时，p1指向最后一个节点，那么这个节点的pNext = NULL;
    //刚好赋值给p2->pNext;
    {
    p2->pNext = NULL;
    free(p1);
    }*/
}
 
 
Node *insertNode(Node *pNode, int findNum, int newNum, datatype data)
{
    Node *p1 = NULL, *p2 = NULL;
     
    p1 = pNode;
    while (p1 != NULL) //找到要插入位置的点
    {
        if (findNum == p1->num)
        {
            //p1保存要插入节点的地址，找到了
         
         
            break;
        }
        else  //否则继续找
        {
            p2 = p1; //p2保存上一个节点
            p1 = p1->pNext; //向前循环
        }
    }
    Node *pnewNode = (Node *)malloc(sizeof(Node));
    pnewNode->num = newNum;
    pnewNode->data = data;
     
     
    if (pNode == p1)
    {
        pnewNode->pNext = pNode;
        pNode = pnewNode; //头插
    }
    else
    {
        pnewNode->pNext = p1;
        p2->pNext = pnewNode;
    }
     
     
    return pNode;
}
 
 
void sortLink(Node *pNode, char ch)
{
    if (ch == '<')  //升序排列
    {
        for (Node *p1 = pNode; p1; p1 = p1->pNext)
        {
            for (Node *p2 = pNode; p2; p2 = p2->pNext)
            {
                if (p1->num > p2->num)
                {
                    struct NODE tNode;
                    tNode.num = p1->num;
                    p1->num = p2->num;
                    p2->num = tNode.num;
                     
                     
                    tNode.data = p1->data;
                    p1->data = p2->data;
                    p2->data = tNode.data;
                }
            }
        }
    }
    else
    {
        if (ch == '>') //降序排列
        {
            for (Node *p1 = pNode; p1; p1 = p1->pNext)
            {
                for (Node *p2 = pNode; p2; p2 = p2->pNext)
                {
                    if (p1->num < p2->num)
                    {
                        struct NODE tNode;
                        tNode.num = p1->num;
                        p1->num = p2->num;
                        p2->num = tNode.num;
                         
                         
                        tNode.data = p1->data;
                        p1->data = p2->data;
                        p2->data = tNode.data;
                    }
                }
            }
        }
    }
}
 
 
int  main()
{
    Node *pNode = NULL;  //链表头结点
     
    pNode = backAddNodeA(pNode, 17, 12);
    pNode = backAddNodeA(pNode, 5, 1254);
    pNode = backAddNodeA(pNode, 9, 1244);
    pNode = backAddNodeA(pNode, 15, 12);
    pNode = backAddNodeA(pNode, 23, 1254);
    pNode = backAddNodeA(pNode, 1144, 1244);
    showAllNode(pNode);
     
    //查找测试代码
    //Node *pfind = searchFirst(pNode, 114);
    //if (pfind == NULL)
    //{
    // printf("没有找到\n");
    //}
    //else
    //{
    // printf("找到了:\n");
    // printf("%p, %d\n%p, %d", pfind, pfind->num, pfind->data, pfind->pNext);
    //}
     
     
    //改变测试代码
    /*change(pNode, 114, 999);
    showAllNode(pNode);*/
     
     
    ////逆转测试代码
    //pNode = reLink(pNode);
    //showAllNode(pNode);
     
     
    ////pNode = deleteNode(pNode, 114);
    //deleteNodeA(&pNode, 114);
    //deleteNodeA(&pNode, 1144);
    //deleteNodeA(&pNode, 11);
     
     
    //头插
    /*pNode = insertNode(pNode, 11, 8, 9);
    pNode = insertNode(pNode, 114, 888, 999);*/
     
     
    //排序测试
    sortLink(pNode, '<');
    showAllNode(pNode);
    sortLink(pNode, '>');
    showAllNode(pNode);
     
    getchar();
}