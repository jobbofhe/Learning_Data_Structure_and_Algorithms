/*
* @Author: jobbofhe
* @Date:   2019-11-11 19:24:34
* @Last Modified by:   Administrator
* @Last Modified time: 2019-11-11 19:55:23
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

	bubble_sort(array, size);

	printf("排序之后： ");
	print(array, size);

	return 0;
}