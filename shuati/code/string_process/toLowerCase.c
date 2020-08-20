/*
* @Author: shuqiang
* @Date:   2020-08-20 20:17:21
* @Last Modified by:   Administrator
* @Last Modified time: 2020-08-20 20:43:03
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * ascii
 *
 * 0 : 48
 * 9 : 57
 * A : 65
 * Z : 90
 * a : 97
 * z : 122
 */

char * toLowerCase(char * str)
{	
	char *tmp = (char*)malloc(sizeof(char)*(strlen(str)+1));

	if (!str) {
		return NULL;
	}

	int i = 0;
	while(*str != '\0') {
		char ch = *str;
		if ('A' <= ch && ch <= 'Z')
		{
			tmp[i] = *str+32;
		}
		else
		{
			tmp[i] = *str;
		}		
		i++;	
		str++;
	}
	tmp[i] = '\0';

	return tmp;
}

void test()
{
	char *str = (char*)malloc(sizeof(char)*36);
	strcpy(str, "HASLKalkjdsALKDSH");

	char *res = toLowerCase(str);

	printf("src:%s\n", str);
	printf("dst:%s\n", res);

	free(str);
	free(res);
}


int main(int argc, char const *argv[])
{
	test();
	return 0;
}