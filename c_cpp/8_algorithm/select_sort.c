
/**
 * 选择排序
 *
 * 思路：
 * 在未排序的数组中找到最小(大)的元素，然后放在数组开始的位置，以此类推，在剩下的元素中找到最小(大)的元素，将其放在已排序的末尾
 *
 * 时间复杂度：O(N2)
 *
 * 稳定性：稳定
 */
#include <stdio.h>

#define LEN(array) ((sizeof(array))/sizeof(array[0]))

void swap(int *a, int *b)
{
	*a = (*a)^(*b);
	*b = (*a)^(*b);
	*a = (*a)^(*b);
}

void select_sort(int a[], int size)
{
	int i, j, min = 0;

	for(i = 0; i < size; i++)
	{
		min = i;
		for (j = i+1; j < size; j++)
		{
			if (a[j] < a[min])
			{
				min = j;
			}
		}
		if (min != i)
		{
			swap(&(a[i]), &(a[min]));
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
	printf("选择排序：\n");
	
	int array[] = {30, 40, 10, 5, 90, 50, 66, 99, 3};
	int size = LEN(array);
	printf("排序之前： ");
	print(array, size);

	select_sort(array, size);

	printf("排序之后： ");
	print(array, size);

	return 0;
}