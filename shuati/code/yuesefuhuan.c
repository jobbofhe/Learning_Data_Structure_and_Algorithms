/*
* @Author: shuqiang
* @Date:   2020-08-10 20:39:13
* @Last Modified by:   Administrator
* @Last Modified time: 2020-08-11 21:43:44
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