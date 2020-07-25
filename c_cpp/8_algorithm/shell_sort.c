/*
* @Author: jobbofhe
* @Date:   2019-11-20 19:20:43
*/

/**
 * 希尔排序：
 * 插入排序的一种，希尔排序是针对直接插入排序算法的改进，又被称为缩小增量排序
 *
 * 基本思想：
 * 	分组插入排序
 * 	对于n个待排序的数列，取一个小于n的整数step(step被称为步长)将待排序元素分成若干个组子序列，
 * 	所有距离为step的倍数的记录放在同一个组中；然后，对各组内的元素进行直接插入排序。 这一趟排
 * 	序完成之后，每一个组的元素都是有序的。然后减小step的值，并重复执行上述的分组和排序。重复这
 * 	样的操作，当step=1时，整个数列就是有序的。
 *
 * 时间复杂度：
 * 	希尔排序的时间复杂度与增量(即，步长gap)的选取有关。例如，当增量为1时，希尔排序退化成了直接插入排序，
 * 	此时的时间复杂度为O(N²)，而Hibbard增量的希尔排序的时间复杂度为O(N3/2)。
 *
 * 稳定性：
 * 	不稳定，因为分组会导致顺序发生变化
 * 
 */
#include <stdio.h>

#define LEN(array) ((sizeof(array))/sizeof(array[0]))

void swap(int *a, int *b)
{
	*a = (*a)^(*b);
	*b = (*a)^(*b);
	*a = (*a)^(*b);
}

void shell_sort(int a[], int size)
{
	int step = 0;

	for (step = size/2; step > 0; step /= 2)
	{
		for (int i = 0; i < step; i++)
		{
			for (int j = i+step; j < size; j+=step)
			{
				if (a[j] < a[j-step])
				{
					int tmp = a[j];
					int k = j-step;

					while (k >= 0 && a[k] > tmp)
					{
						a[k+step] = a[k];
						k -= step;
					}
					a[k+step] = tmp;
				}
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
	printf("希尔排序：\n");
	
	int array[] = {30, 40, 10, 5, 90, 50, 66, 99, 3};
	int size = LEN(array);
	printf("排序之前： ");
	print(array, size);

	shell_sort(array, size);

	printf("排序之后： ");
	print(array, size);

	return 0;
}