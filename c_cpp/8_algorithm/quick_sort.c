/*
* @Author: jobbofhe
* @Date:   2019-11-22 17:19:51
*/

/**
 * 快速排序：
 * 	基本思想：分治法策略。
 * 	选择一个基准数，通过一趟排序将要排序的数据分割成独立的两部分；其中一部分的所有数据都比另外一部分的所有数据都要小。
 * 	然后，再按此方法对这两部分数据分别进行快速排序，整个排序过程可以递归进行，以此达到整个数据变成有序序列。
 *
 * 快速排序流程：
 * 	(1) 从数列中挑出一个基准值。
 *  (2) 将所有比基准值小的摆放在基准前面，所有比基准值大的摆在基准的后面(相同的数可以到任一边)；在这个分区退出之后，该基准就处于数列的中间位置。
 *  (3) 递归地把"基准值前面的子数列"和"基准值后面的子数列"进行排序。
 *
 * 时间复杂度：
 * 	快速排序的时间复杂度在最坏情况下是O(N2)，平均的时间复杂度是O(N*lgN)。
 * 	这句话很好理解：假设被排序的数列中有N个数。遍历一次的时间复杂度是O(N)，需要遍历多少次呢？至少lg(N+1)次，最多N次。
 * 	(01) 为什么最少是lg(N+1)次？快速排序是采用的分治法进行遍历的，我们将它看作一棵二叉树，它需要遍历的次数就是二叉树的深度，
 * 		而根据完全二叉树的定义，它的深度至少是lg(N+1)。因此，快速排序的遍历次数最少是lg(N+1)次。
 * 	(02) 为什么最多是N次？这个应该非常简单，还是将快速排序看作一棵二叉树，它的深度最大是N。因此，快读排序的遍历次数最多是N次。
 * 
 * 稳定性：
 * 	快速排序是不稳定的算法，它不满足稳定算法的定义。
 */
#include <stdio.h>

#define LEN(array) ((sizeof(array))/sizeof(array[0]))

void swap(int *a, int *b)
{
	*a = (*a)^(*b);
	*b = (*a)^(*b);
	*a = (*a)^(*b);
}

/**
 * @param a        [待排序数组]
 * @param l_border [数组左边界]
 * @param r_border [数组右边界]
 */
void quick_sort(int a[], int l_border, int r_border)
{
	if (l_border < r_border)
	{
		int l, r, tmp;

		l = l_border;
		r = r_border;
		tmp = a[l];

		while(l < r) 
		{
			// 如果右边的值大于基准, 则继续向前访问
			while (l < r && a[r] > tmp)
			{
				r--;
			}
			// 如果还是乱序，则说明右边的值小于基准，则交换顺序
			if (l < r)
			{
				a[l++] = a[r];
			}

			// 如果左边的值小于基准，继续向前访问
			while(l < r && a[l] < tmp)
			{
				l++;
			}
			// 如果还是乱序，说明左边的值大于基准，需要交换
			if (l < r)
			{
				a[r--] = a[l];
			}
		}
		// 停下来的位置，就是基准的所在位置
		a[l] = tmp;
		quick_sort(a, l_border, l-1);
		quick_sort(a, l+1, r);

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
	printf("快速排序：\n");
	
	int array[] = {30, 40, 10, 5, 90, 50, 66, 99, 3};
	int size = LEN(array);
	printf("排序之前： ");
	print(array, size);

	quick_sort(array, 0, size - 1);

	printf("排序之后： ");
	print(array, size);

	return 0;
}