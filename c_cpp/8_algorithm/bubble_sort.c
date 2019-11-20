/*
* @Author: jobbofhe
* @Date:   2019-11-11 19:24:34
* @Last Modified by:   Administrator
* @Last Modified time: 2019-11-18 19:13:48
*/

/**
 * 冒泡排序
 *
 * 冒泡排序时间复杂度
 * 冒泡排序的时间复杂度是 O(N2)。
 * 假设被排序的数列中有N个数。遍历一趟的时间复杂度是O(N)，需要遍历多少次呢？N-1次！因此，冒泡排序的时间复杂度是O(N2)。
 * 
 * 冒泡排序稳定性
 * 冒泡排序是稳定的算法，它满足稳定算法的定义。
 * 算法稳定性 -- 假设在数列中存在a[i]=a[j]，若在排序之前，a[i]在a[j]前面；并且排序之后，a[i]仍然在a[j]前面。则这个排序算法是稳定的！
 * 
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

