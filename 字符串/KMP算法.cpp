#include<bits/stdc++.h>
using namespace std;
//获得next数组
vector<int>get_next(string& s)
{
	if (s.size() == 1)
	{
		vector<int>result(1, -1);
		return result;
	}
	vector<int>result(s.size());
	result[0] = -1;
	result[1] = 0;
	int i = 2, cn = 0;//i表示当前要获得的next数组中的值，cn表示当前要比对的下标（前一个位置next数组的值）
	while (i < s.size())
	{
		if (s[i - 1] == s[cn])result[i++] = ++cn;//比对到相同时，此处next数组的值为cn+1，更新cn的值方便下一个数用
		else if (cn > 0)cn = result[cn];//比对到不同而且还能往前蹦
		else result[i++] = 0;//比对到不同，但不能蹦了，cn=0
	}
	return result;
}
//KMP算法（字符串匹配）
int kmp(string& s1, string& s2)
{
	int n = s1.size(), m = s2.size();
	int x = 0, y = 0;//x为s1当前比对的位置，y为s2当前比对的位置
	vector<int>next = get_next(s2);
	while (x < n && y < m)
	{
		if (s1[x] == s2[y])
		{
			x++;
			y++;
		}//如果正常能匹配上，都加一
		else if (y == 0)x++;//如果匹配不上且s2在匹配第一个字符，直接匹配s1的下一个字符
		else y = next[y];//s2不在匹配第一个字符，匹配next数组
	}
	return y == m ? x - y : -1;//最终s2到头了，返回位置，否则返回-1
}
int main()
{
	string s1, s2;
	cin >> s1 >> s2;
	cout << kmp(s1, s2) << endl;
	return 0;
}