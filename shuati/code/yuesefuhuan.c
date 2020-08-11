/*
* @Author: shuqiang
* @Date:   2020-08-10 20:39:13
* @Last Modified by:   Administrator
* @Last Modified time: 2020-08-11 22:56:23
*/

/**
 * 问题：
 * N个人围成一圈，第一个人从1开始报数，报M的将被杀掉，下一个人接着从1开始报。如此反复，最后剩下一个，求最后的胜利者。
 *
 * 思路：
 * 1. 循环列表完成，每次被“杀掉的人”，其节点被删除，时间复杂度 O(mn)
 * 2. 公式法
 * 因此我们可以推出递推公式f(8,3) = [f(7, 3) + 3] \% 8f(8,3)=[f(7,3)+3]%8
 * 进行推广泛化，即f(n,m) = [f(n-1, m) + m] \% nf(n,m)=[f(n−1,m)+m]%n
 */


int joseph(int m, int k)
{
	int position = 0;

	for (int i = 2; i <= m; ++i)
	{
		position = (position + k) % i;
	}

	return position;

}

void test_joseph()
{
	int pos = joseph(30, 7);
	printf("最终活下来的人是第[%d]个\n", pos);
}

int main(int argc, char const *argv[])
{
	test_joseph();

	return 0;
}