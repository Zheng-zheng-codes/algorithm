#include<bits/stdc++.h>
using namespace std;
vector<int> z_array(string& s)
//z数组（z[i]）：从i出发的字符串与原字符串最长有多长的公共前缀
{
	vector<int>z(s.size());
	z[0] = s.size();
	for (int i = 1, c = 1, r = 1,len; i < s.size(); i++)
		//i为当前的位置，c为目前扩到的边界的中心，r为目前扩到的最右边界，len为此处的前缀长度
	{
		len = i < r ? min(r - i, z[i - c]) : 0;//如果能被包住，先在两种情况中取最小的，包不住时取0
		while (i + len < s.size() && s[i + len] == s[len])len++;//取最小后再往后扩，获得了以i为启示的前缀长度len
		if (i + len > r)
		{
			r = i + len;
			c = i;
		}
		z[i] = len;
	}
	return z;
}
vector<int>e_array(string& a,string&b)
//e数组（e[i]）：a从i开始的后缀与b的公共前缀
{
	vector<int>e(a.size());
	vector<int>zb = z_array(b);
	for (int i = 0, c = 0, r = 0, len; i < a.size(); i++)
	{
		len = i < r ? min(zb[i - c], r - i) : 0;
		while (i + len < a.size() && len < b.size() && a[i + len] == b[len])len++;
		if (i + len > r)
		{
			r = i + len;
			c = i;
		}
		e[i] = len;
	}
	return e;
}
int main()
{
	string s;
	cin >> s;
	vector<int>z = z_array(s);
	for (int i = 0; i < z.size(); i++)cout << z[i] << " ";
	cout << endl;
	string a, b;
	cin >> a >> b;
	vector<int>e = e_array(a,b);
	for (int i = 0; i < e.size(); i++)cout << e[i] << " ";
	return 0;
}