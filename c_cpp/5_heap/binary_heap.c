/*
* @Author: jobbofhe
* @Date:   2019-10-14 19:21:57
* @Last Modified by:   Administrator
* @Last Modified time: 2019-10-15 15:21:49
*/

#include <stdio.h>
#include <stdlib.h>

#define ARRAY_LEN(arr) ((sizeof(arr))/sizeof(arr[0]))

#define MAX_NUM (128)

typedef int Type;

static Type heap_arr[MAX_NUM];
static int  heap_size = 0; // 堆数组的大小

/**
 * 根据数据 data 从对中获取对应的索引
 * @param  data [description]
 * @return      [description]
 */
int get_data_index_from_heap(int data)
{
    for (int i = 0; i < heap_size; ++i)
    {
        if (data == heap_arr[i])
        {
            return i;
        }
    }

    return -1;
}

/**
 * 在数组实现的堆中，向下调整元素的位置，使之符合大根堆
 * 注：   
 *     在数组试下你的堆中，第 i 个节点的
 *     左孩子的下标是 2*i+1， 
 *     右孩子的下标是 2*i+2,
 *     父节点的下标是 (i-1)/2
 *     
 * @param  start [一般从删除元素的位置开始]
 * @param  end   [数组的最后一个索引]
 */
static void max_heap_fixup_down(int start, int end)
{
    int curr_node_pos = start;
    int left_child = 2*start+1;
    int curr_node_data = heap_arr[curr_node_pos];



    while(left_child <= end) 
    {

        // left_child 是左孩子， left_child+1是同一个父节点下的右孩子
        if (left_child < end && heap_arr[left_child] < heap_arr[left_child+1])
        {
            // 从被删除的节点的左右孩子中选取较大的，赋值给父节点
            left_child++;
        }
        if (curr_node_data >= heap_arr[left_child])
        {
            // 选出孩子节点的较大者之后，与当前节点比较
            break;
        }
        else
        {
            heap_arr[curr_node_pos] = heap_arr[left_child];
            curr_node_pos = left_child;
            left_child = 2*left_child+1;
        }
    }

    heap_arr[curr_node_pos] = heap_arr[left_child];
}

/**
 * 删除对中的数据 data
 * @param data [description]
 */
static int max_heap_delete(int data)
{
    if (heap_size == 0)
    {
        printf("堆已空!\n");
        return -1;
    }
    int index = get_data_index_from_heap(data);
    if (index < 0)
    {
        printf("删除失败, 数据 [%d] 不存在!\n", data);
        return -1;
    }

    // 删除index的元素，使用最后的元素将其替换
    heap_arr[index] = heap_arr[--heap_size];

    // 删除元素之后，调整堆
    max_heap_fixup_down(index, heap_size-1);
}

/**
 * 在数组实现的堆中，将元素向上调整
 * 注：   
 *     在数组试下你的堆中，第 i 个节点的
 *     左孩子的下标是 2*i+1， 
 *     右孩子的下标是 2*i+2,
 *     父节点的下标是 (i-1)/2
 *     
 * @param  start [从数组的最后一个元素开始，start是最后一个元素的下标]
 */
static void max_heap_fixup_up(int start)
{
    int curr_node_pos = start;
    int parent = (start-1)/2;
    int curr_node_data = heap_arr[curr_node_pos];

    // 从最后一个元素开始比价，知道第0个元素
    while(curr_node_pos > 0) 
    {   
        // 当前节点的数据小于父节点，退出
        if (curr_node_data <= heap_arr[parent])
        {
            break;
        }
        else
        {
            // 交换父节点和当前节点
            heap_arr[curr_node_pos] = heap_arr[parent];
            heap_arr[parent] = curr_node_data;

            curr_node_pos = parent;
            parent = (parent-1)/2;
        }
    }
}

/**
 * 将新数据插入到二叉堆中
 * @param  data [插入数据]
 * @return      [成功返回0， 失败返回-1]
 */
int max_heap_insert(Type data)
{
    if (heap_size == MAX_NUM)
    {
        printf("堆已经满了！\n");
        return -1;
    }

    heap_arr[heap_size] = data;
    // 调整堆 
    max_heap_fixup_up(heap_size);
    heap_size++; // 对的数量自增

    return 0;
}

/**
 * 打印二叉堆
 */
void max_heap_print()
{
    for (int i = 0; i < heap_size; ++i)
    {
        printf("%d ", heap_arr[i]);
    }
}

int main(int argc, char const *argv[])
{
    Type tmp[] = {10, 40, 30, 60, 90, 70, 20, 50, 80};
    int len = ARRAY_LEN(tmp);

    printf("---> 添加元素：\n");
    for (int i = 0; i < len; ++i)
    {
        printf("%d ", tmp[i]);
        max_heap_insert(tmp[i]);
    }   

    printf("\n---> 最大堆: ");
    max_heap_print();

    max_heap_insert(85);
    printf("\n---> 插入元素之后 最大堆: ");
    max_heap_print();


    max_heap_delete(90);
    printf("\n---> 删除元素之后 最大堆: ");
    max_heap_print();
    printf("\n");



    return 0;
}