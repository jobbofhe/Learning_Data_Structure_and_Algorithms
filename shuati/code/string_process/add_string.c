#include <stdlib.h>
#include <stdlib.h>
#include <string.h>

/**
 * 字符串相加，字符串中的字符范围 '0' - '9'
 * 要求：不允许将字符串转换为 整数
 */

char * addStrings(char * num1, char * num2){
    int i = strlen(num1) - 1;
    int j = strlen(num2) - 1;

    int max = i > j ? i : j;
    // +3 的原因： i j 分别减去了1，还有进位考虑
    char *res = (char*)malloc(sizeof(char)*(max+3));

    int k = 0;
    int add = 0; // 进位
    while(i >=0 || j >= 0 || add != 0)
    {   
        int x, y;
        int plus = 0;
        if (i < 0)
        {
            x = 0;
        }
        else
        {
            x = num1[i] - '0';
        }
        if (j < 0)
        {
            y = 0;
        }
        else
        {
            y = num2[j] - '0';
        }

        plus = x+y+add;
        res[k++] = '0'+plus%10;
        add = plus/10;
        i--;
        j--;
    }

    for (int i = 0; 2*i < k; ++i)
    {
        int tmp = res[i];
        res[i] = res[k-i-1];
        res[k-i-1] = tmp;
    }
    res[k++] = 0;

    return res;
}

void test()
{
	char *num1 = "7891546";
	char *num2 = "123";
	char *res = addStrings(num1, num2);
	printf("num1+num2 = : %s + %s = %s\n", num1, num2, res);
	free(res);

	num1 = "7891546";
	num2 = "0";
	res = addStrings(num1, num2);
	printf("num1+num2 = : %s + %s = %s\n", num1, num2, res);
	free(res);

	num1 = "7891546";
	num2 = "9";
	res = addStrings(num1, num2);
	printf("num1+num2 = : %s + %s = %s\n", num1, num2, res);
	free(res);
}

int main(int argc, char const *argv[])
{
	test();


	return 0;
}