/**
 * 连个字符串：
 * srcstr 和 substr， 找出substr 第一次出现在 srcstr的位置，如果不存在换回 -1
 */


#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int strStr(char *haystack, char *needle)
{
	int len1 = strlen(haystack);
	int len2 = strlen(needle);
	int flag = 0;

	if (len1 == 0 && len2 == 0)
	{
		return 0;
	}

	for (int i = 0; i < len1; ++i)
	{
		flag = 0;
		for (int j = 0; j < len2; ++j)
		{
			if (haystack[i+j] != needle[j])
			{
				flag = 1;
				break;
			}
		}
		if (flag == 0)
		{
			return i;
		}
	}

	return -1;
}

void test()
{
	char haystack[] = "akjsdhgoiaerlkajgh";
	char needle[] = "aer";

	int pos = strStr(haystack, needle);
	printf("%d\n", pos);
}

int main(int argc, char const *argv[])
{
	test();

	return 0;
}