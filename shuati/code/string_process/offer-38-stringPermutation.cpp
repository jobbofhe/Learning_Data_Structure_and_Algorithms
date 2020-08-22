#include <iostream>
#include <vector>
#include <set>

/**
 * 字符串的全排列个数
 * 举例："abc"
 * 拍全列： abc acb bac bca cab cba
 */

void backtrack(std::string s, int start, std::set<std::string> &res)
{
	// 回溯结束条件
	if (start == s.size())
	{
		res.insert(s);
		return;
	}

	for (int i = start; i < s.size(); ++i)
	{
		std::swap(s[i], s[start+1]);
		backtrack(s, start+1, res);
		std::swap(s[i], s[start+1]);
	}
}

std::vector<std::string> permutation(std::string s)
{
	// 去重处理
	std::set<std::string> res;
	backtrack(s, 0, res);

	return std::vector<std::string>(res.begin(), res.end());
}

int main(int argc, char const *argv[])
{
	std::string src("jobfhe");
	std::cout << src << std::endl;
	std::vector<std::string> res = permutation(src);
	std::cout << res.size() << std::endl;

	return 0;
}