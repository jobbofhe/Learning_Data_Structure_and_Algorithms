#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * 原地反转
 */
void revers(char*sub_str, int start, int end) {
    char tmp;
    while (start < end) {
        tmp = sub_str[start];
        sub_str[start] = sub_str[end];
        sub_str[end] = tmp;
        start++;
        end--;
    }
}
char * reverseWords(char * s){
    int i = 0;
    int start = 0;
    int len = strlen(s);

    while (s[i++] != '\0') {
        
        if (s[i] == ' ') {
            revers(s, start, i-1);
            start = i+1;
        }

        if (i == len-1) {
            revers(s, start, i);
        }
    }
    
    return s;
}

void test()
{
	char a[30] = "helo leecode 353456";
	printf("src: %s\n", a);
	char *res = reverseWords(a);

	printf("dst: %s\n", res);
}

int main(int argc, char const *argv[])
{
	test();

	return 0;
}