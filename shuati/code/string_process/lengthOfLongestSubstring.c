/**
 * 求字符串的最长字串长度
 */

#include <stdio.h>

int lengthOfLongestSubstring(char * s)
{
    int i, j = 0, count = 0, max = 0, index[128] = {0}, start = 0;

    for(i=0;s[i]!='\0';i++)     
    {
    	// 如果当前字符 出现过
        if(index[s[i]]>start)   //index用来储存出现重复字符时
        {                       //子串起始下标应移动到的地方
        	// 则当前子串的长度记为 count
            count = i-start;
            // 如果当前子串的长度大于最大长度，则更新最大长度的值
            if(count>max)
            {
                max = count;
            }

            // 更新起始位置
            start = index[s[i]];

            //printf("***: i:%3d | s[i]: %3d %c index[s[i]]: %3d  count:%3d start:%3d max:%d\n", i, s[i], s[i], index[s[i]], count, start, max);
        }
        index[s[i]] = i+1;

        printf("---: i:%3d | s[i]: %3d %c index[s[i]]: %3d  count:%3d start:%3d max:%d\n", i, s[i], s[i], index[s[i]], count, start, max);
    }
    count = i-start;

    printf("count: %d max:%d\n", count, max);
    return count>max?count:max;
}

int main(int argc, char const *argv[])
{
	char s[32] = "jobbofhe";
	printf("src: %s\n", s);

	int count = lengthOfLongestSubstring(s);

	printf("lengthOfLongestSubstring: %d\n", count);

	return 0;
}
