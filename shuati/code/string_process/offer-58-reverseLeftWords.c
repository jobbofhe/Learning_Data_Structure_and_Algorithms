#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* reverseLeftWords(char* s, int n){
    if (!s)
    {
        return NULL;
    }

    int len = strlen(s);
    char *sret = (char*)malloc(sizeof(char)*(len+1));
    memset(sret, 0, sizeof(char)*(len+1));
    
    char *p1 = s;
    char *p2 = s;
    char *ret = sret;
    int count = n;

    // 找到后一个字符串的指针位置
    while(n--)
    {
        p2++;
    }

    // 将后一个指针的数据拷贝至返回值中
    while(*p2)
    {
        *ret++ = *p2++;
    }

    // 将字符串前半部分，拷贝至返回值中
    while(count--)
    {
        *ret++ = *p1++;
    }

    return sret;
}

int main(int argc, char const *argv[])
{
	printf("左侧字符串逆序：\n");
	char str[10000] = "123fanlu";
    printf("src string: %s\n", str);

	char *pStr = reverseLeftWords(str, 3);
	printf("%s\n", 	pStr);	
	
	return 0;
}