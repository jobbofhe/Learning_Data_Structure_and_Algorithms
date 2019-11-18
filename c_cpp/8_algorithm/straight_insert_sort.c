/*
* @Author: jobbofhe
* @Date:   2019-11-18 19:10:24
* @Last Modified by:   Administrator
* @Last Modified time: 2019-11-18 19:46:47
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
		for (j = i-1; j >= 0; j--)
		{
			// 
			if (a[j] < a[i])
			{
				break;
			}
		}

		// 如果第 j 个 与第i个不相邻，则交换位置
		if (j != i-1)
		{
			int tmp = a[i];

			for (k = i-1; k > j; k--)
			{
				a[k+1] = a[k];
			}
			a[k+1] = tmp;
		}
		/* code */
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

	insert_sort(array, size);

	printf("排序之后： ");
	print(array, size);

	return 0;
}