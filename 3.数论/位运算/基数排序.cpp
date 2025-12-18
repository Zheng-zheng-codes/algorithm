//基数排序前提：样本是整数
//整体思路：从个位开始排序，再给十位排序……（这样可以让十位一样个位不一样的数顺序正常）
#include<bits/stdc++.h>
using namespace std;
const int maxn = 500000;
const int BASE = 10;
int temp[maxn];
int cnts[BASE];
int bits(int num)
{
	if (num == 0)return 1;
	int ans = 0;
	while (num > 0)
	{
		ans++;
		num /= BASE;
	}
	return ans;
}//获取数字在BASE进制下的位数
void radixsort(int bits, vector<int>& nums)
//bits是nums中的最大值在BASE进制下的位数
{
	for (int offset = 1; bits > 0; offset *= BASE, bits--)
	{
		memset(cnts, 0, sizeof(cnts));//把cnts里的元素全赋值为0（注意是sizeof(cnts)）字节数不是元素个数
		for (int i = 0; i < nums.size(); i++)cnts[(nums[i] / offset) % BASE]++;//统计每个数字的个数
		for (int i = 1; i < BASE; i++)cnts[i] += cnts[i - 1];//获取前缀和
		for (int i = nums.size() - 1; i >= 0; i--)temp[--cnts[(nums[i] / offset) % BASE]] = nums[i];
		//从后往前排序
		for (int i = 0; i < nums.size(); i++)nums[i] = temp[i];
	}
}
void sortarray(vector<int>& nums)
{
	int minnum = nums[0];
	for (int i = 1; i < nums.size(); i++)minnum = min(minnum, nums[i]);//获取最小值用来解决负数的问题
	int maxnum = 0;
	for (int i = 0; i < nums.size(); i++)
	{
		nums[i] -= minnum;
		maxnum = max(maxnum, nums[i]);
	}
	radixsort(bits(maxnum), nums);
	for (int i = 0; i < nums.size(); i++)nums[i] += minnum;//排序后再把最小值都加上
}
int main()
{
	int n;
	cin >> n;
	vector<int>nums(n);
	for (int i = 0; i < n; i++)cin >> nums[i];
	sortarray(nums);
	for (int i = 0; i < n; i++)cout << nums[i] << " ";
	return 0;
}