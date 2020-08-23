/**
 * 题目：给出一个数字字符串 ：  "132456789"
 * 要求按照千分位，分割， 结果就是 "132.456.789"
 */

#include <iostream>
#include<algorithm>

using namespace std;

void test();

class thousandSeparator
{
public:

	thousandSeparator()
	{
		
	}

	string solve(int n)
	{
		int count = 0;
		string res;

		do {
			res.push_back(n%10 + '0');
			n /= 10;
			count++;
			if (count % 3 == 0 && n != 0)
			{
				res.push_back('.');
			}
		}while(n > 0);

		reverse(res.begin(), res.end());
		return res;
	}	
};


void test()
{
	int n = 1234567;
	thousandSeparator obj;
	
	string res = obj.solve(n);
	std::cout << "src: "<< n << " - " << "res: " << res << std::endl;
}

int main(int argc, char const *argv[])
{
	test();

	return 0;
}