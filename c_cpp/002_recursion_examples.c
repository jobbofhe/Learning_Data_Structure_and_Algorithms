/**
 * 递归
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define     TRUE    (1)
#define     FALSE   (0) 

typedef int Status;

/**
 * -- 1. 递归的形象解释： 
 * 就像俄罗斯套娃一样，从最外边一层一层打开，直到最后一层打开之后，发现里边
 * 再也没有可以打开的了（递归结束条件），然后从里到外，又一层一层装起来。
 */

/**
 * -- 2. 递归三要素：
 * 递归终止条件
 * 递归终止处理办法
 * 提取重复的逻辑，缩小问题规模
 */

/**
 * -- 3. 递归代码实现模型
 */
/*
int recursion(大规模)
{
    if(end condition)
    {
        end_function();
    }
    else
    {
        // 接续递归
        recursion(小规模);
    }
}
*/

/**
 * -- 4. 递归常用的场景
 * (1). 问题的定义是按递归定义的（Fibonacci函数，阶乘，…）
　* (2). 问题的解法是递归的（有些问题只能使用递归方法来解决，例如，汉诺塔问题，…）
　* (3). 数据结构是递归的（链表、树等的操作，包括树的遍历，树的深度，…）。
 */

/**
 * 阶乘
 */
int recursion_factorial(int n)
{
    if (n == 1)
    {
        return 1;
    }
    else
    {
        return n * recursion_factorial(n-1);
    }
}

/**
 * 斐波那契数列
 */
int recursion_fibonacc(int pre, int curr, int n)
{
    if (n < 0)
    {
        return -1;
    }
    if (n == 1)
    {
        return pre;
    }
    else if (n == 2)
    {
        return curr;
    }
    else
    {
        return recursion_fibonacc(curr, pre+curr, n - 1);
    }
}

/**
 * 杨辉三角
 */
int recursion_yanghui_triangle(int at_x, int at_y)
{

    if (at_y <= at_x && at_y >= 0)
    {
         if (at_y == 0 || at_x == at_y)
        {
            return 1; // 递归终止条件
        }
        else
        {
            return recursion_yanghui_triangle(at_x-1, at_y-1) + recursion_yanghui_triangle(at_x-1, at_y);
        }
    }
   
}

/**
 * 二分查找
 */
int recursion_search(int *array, int low, int high, int target)
{
    if(low <= high)
    {
        int mid = (low+high) / 2;
        if(array[mid] == target)
        {
            return mid+1;
        }
        else if (array[mid] > target)
        {
            return recursion_search(array, low, mid-1, target);
        }
        else
        {
            return recursion_search(array, mid+1, high, target);
        }
    }
    return -1;
}


int main(int argc, char const *argv[])
{   
    int num_factorial = 0;
    int num_fibonacc = 0;
    int num_yanghui = 0;
    int num_search = 0;

    num_factorial = recursion_factorial(3);
    num_fibonacc = recursion_fibonacc(1, 1, 6);
    num_yanghui = recursion_yanghui_triangle(3, 2);

    int array[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    num_search = recursion_search(array, 0, 9, 3);

    printf("num_factorial=%d\n", num_factorial);
    printf("num_fibonacc=%d\n", num_fibonacc);
    printf("num_yanghui=%d\n", num_yanghui);
    printf("num_search=%d\n", num_search);

    return 0;
}