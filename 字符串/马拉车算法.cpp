#include<bits/stdc++.h>
using namespace std;
//获得扩展串
string convert(string& s)
{
	int n = s.size() * 2 + 1;
	string ss;
	for (int i = 0, j = 0; i < n; i++)
	{
		ss += (i & 1) == 0 ? '#' : s[j++];
	}
	return ss;
}
//Manacher算法（获得最大回文子串长度）
int Manacher(string& s)
{
	string ss = convert(s);
	vector<int>p(ss.size());//每个点的最长回文半径
	int max_r = 0;//max_r为最大的回文半径，减一即为最大回文子串长度
	for (int i = 0, c = 0, r = 0, len; i < ss.size(); i++)
		//i为当前的中心位置，c为回文中心，r为回文覆盖最右边界，len为当前求出的此处的回文半径
	{
		len = i < r ? min(p[2 * c - i], r - i) : 1;//如果能被包住，先在两种情况中取最小的，包不住时取1
		while (i - len >= 0 && i + len < ss.size() && ss[i - len] == ss[i + len])len++;
		//取最小后再往两边扩，获得了以i为中心的回文半径len
		if (i + len > r)
		{
			c = i;
			r = i + len;
		}
		max_r = max(len, max_r);
		p[i] = len;
	}
	return max_r - 1;
}
int main()
{
	string s;
	cin >> s;
	cout << Manacher(s) << endl;
	return 0;
}