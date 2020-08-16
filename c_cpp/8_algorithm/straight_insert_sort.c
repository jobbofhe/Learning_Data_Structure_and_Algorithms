/*
* @Author: jobbofhe
* @Date:   2019-11-18 19:10:24
* @Last Modified by:   Administrator
* @Last Modified time: 2020-08-17 00:17:38
*/

/**
 *
 * 直接插入排序的思路：
 * 
 * 把n个待排序的元素看成为一个有序表和一个无序表。开始时有序表中只包含1个元素，
 * 无序表中包含有n-1个元素，排序过程中每次从无序表中取出第一个元素，将它插入
 * 到有序表中的适当位置，使之成为新的有序表，重复n-1次可完成排序过程。
 *
 * 时间复杂度： O(N2) 假设被排序的数列中有N个数。遍历一趟的时间复杂度是O(N)，需要遍历多少次呢？N-1！因此，直接插入排序的时间复杂度是O(N2)。
 *
 * 稳定性：是稳定算法
 */

#include <stdio.h>

#define LEN(array) ((sizeof(array))/sizeof(array[0]))

void insert_sort(int a[], int n)
{
	int i, j, k;

	for (i = 1; i < n; ++i)
	{
		printf("[%d]-------------------------------------------------------------------------\n", i);
		// 找到插入位置
		for (j = i-1; j >= 0; j--)
		{
			printf("比较： i:%d, j:%d a[%d]:%d a[%d]:%d\n", i, j, i, a[i], j, a[j]);
			// 从小到大排序
			if (a[j] < a[i])
			{
				break;
			}
		}

		// 如果第 j 个 与第i个不相邻，则交换位置
		if (j != i-1)
		{
			int tmp = a[i];
			printf("j: %d, i-1: %d\n", j, i-1);
			for (k = i-1; k > j; k--)
			{
				a[k+1] = a[k];
				printf("\n交换： k:%d, a[%d]:%d", k, k+1, a[k+1]);
			}
			a[k+1] = tmp;
			printf(", a[%d]: %d\n", k+1, a[k+1]);
		}
	}
}


void insert_sort_v2(int a[], int n)
{
	int i = 0, j = 0;

	for (i = 1; i < n; ++i)
	{
		int value = a[i];
		j = i-1;
		// 将a[i], 插入有序数组a[j]中
		for (; j >= 0; --j)
		{
			if (a[j] > value)
			{
				a[j+1] = a[j];
			}
			else
			{
				break;
			}
		}
		a[j+1] = value;
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

void test_insert_sort_1()
{
	int array[] = {30, 40, 10, 5, 90, 50, 66, 99, 3};
	int size = LEN(array);
	printf("排序之前： ");
	print(array, size);

	insert_sort(array, size);

	printf("排序之后： ");
	print(array, size);
}

void test_insert_sort_2()
{
	int array[] = {30, 40, 10, 5, 90, 50, 66, 99, 3};
	int size = LEN(array);
	printf("排序之前： ");
	print(array, size);

	insert_sort_v2(array, size);

	printf("排序之后： ");
	print(array, size);
}

int main(int argc, char const *argv[])
{
	printf("直接插入排序：\n");
	
	test_insert_sort_1();

	test_insert_sort_2();

	return 0;
}