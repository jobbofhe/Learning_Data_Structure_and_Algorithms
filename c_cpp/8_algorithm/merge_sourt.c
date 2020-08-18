#include <stdio.h>
#include <stdlib.h>

void merge(int a[], int start, int mid, int end);

void merge_sort(int a[], int start, int end)
{
	int mid = start+(end-start)/2;

	if (start >= end)
	{
		return;
	}
	merge_sort(a, start, mid);
	merge_sort(a, mid+1, end);

	merge(a, start, mid, end);
}

void merge(int a[], int start, int mid, int end)
{
	int *tmp = (int*)malloc(sizeof(int)*(end-start+1));
	int i = start;
	int j = mid + 1;
	int k = 0;

	while(i < mid && j <= end) 
	{
		if (a[i] <= a[j])
		{
			tmp[k++] = a[i++];
		}
		else
		{
			tmp[k++] = a[j++];
		}
	}

	while(i <= mid) 
	{
		tmp[k++] = a[i++];
	}
	while(j <= end) 
	{
		tmp[k++] = a[j++];
	}

	for (i = 0; i < k; ++i)
	{
		a[start+i] = tmp[i];
	}

	free(tmp);
}

void test_merge_sort()
{
	int a[] = {33, 55, 1, 3, 77, 7, 88, 9, 0, 100};

	int size = sizeof(a)/sizeof(a[0]);

	
	printf("排序前：\n");
	for (int i = 0; i < size; ++i)
	{
		printf("%d ", a[i]);
	}
	printf("\n");

	merge_sort(a, 0, size-1);

	printf("排序后：\n");
	for (int i = 0; i < size; ++i)
	{
		printf("%d ", a[i]);
	}
	printf("\n");

}

int main(int argc, char const *argv[])
{
	test_merge_sort();

	return 0;
}