
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * 字符串的最后一个单词的长度，单词以空格隔开
 */

int lengthOfLastWord(char * s)
{
	int len = strlen(s);
	char *p = s;
	int cnt = 0;

	if (len == 0)
	{
		return 0;
	}

	for (int i = len-1; i >= 0; --i)
	{
		if (p[i] != ' ')
		{
			cnt++;
		}
		else if (cnt != 0)
		{
			break;
		}
	}

	return cnt;
}

void test()
{
	char a[36] = "hello leetoce java dachang";

	int count = lengthOfLastWord(a);

	printf("src: %s\n", a);
	printf("count: %d\n", count);
}

int main(int argc, char const *argv[])
{
	test();

	return 0;
}