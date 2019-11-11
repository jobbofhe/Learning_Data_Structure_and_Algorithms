/*
* @Author: jobbofhe
* @Date:   2019-11-11 19:24:34
* @Last Modified by:   Administrator
* @Last Modified time: 2019-11-11 19:56:27
*/

/**
 * 冒泡排序
 */
#include <stdio.h>

#define LEN(array) ((sizeof(array))/sizeof(array[0]))

void print(int a[], int size);

void swap(int *a, int *b)
{
	*a = (*a)^(*b);
	*b = (*a)^(*b);
	*a = (*a)^(*b);
}

/**
 * 每一趟排序，将最大元素放在数组的末尾
 * 缺点：
 * 	数组一旦有序之后，后边的循环还在进行，每次比较就是在浪费时间
 */
void bubble_sort(int a[], int size)
{
	for (int i = size-1; i > 0; i--)
	{
		for (int j = 0; j < i; j++)
		{
			if (a[j] > a[j+1])
			{
				swap(&(a[j]), &(a[j+1]));
			}
		}
	}
}

/**
 * 改进上述接口的缺点
 * 改进方法：一旦数组有序之后则停止排序
 */
void bubble_sort_v2(int a[], int size)
{
	int flag= 0;

	for (int i = size-1; i > 0; i--)
	{
		flag = 0;
		for (int j = 0; j < i; j++)
		{
			if (a[j] > a[j+1])
			{
				swap(&(a[j]), &(a[j+1]));
				flag = 1;   // 数组无序，发生交换，交换标识记为1
			}
		}

		// 如果循环一次之后，发现标识为0，说明，数组已经有序
		if (0 == flag)
		{
			break;
		}
	}
}


void print(int a[], int size)
{
	for (int i = 0; i < size; ++i)
	{
		printf(" %d", a[i]);
	}
	printf("\n");
}

int main(int argc, char const *argv[])
{
	int array[] = {30, 40, 10, 5, 90, 50, 66, 99, 3};
	int size = LEN(array);
	printf("排序之前： ");
	print(array, size);

	// bubble_sort(array, size);
	bubble_sort_v2(array, size);

	printf("排序之后： ");
	print(array, size);

	return 0;
}