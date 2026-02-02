/*
现在你总共有 numCourses 门课需要选，记为 0 到 numCourses - 1。
给你一个数组 prerequisites ，其中 prerequisites[i] = [ai, bi] ，表示在选修课程ai前必须先选修 bi 。
例如，想要学习课程 0 ，你需要先完成课程 1 ，我们用一个匹配来表示：[0,1] 。
返回你为了学完所有课程所安排的学习顺序。可能会有多个正确的顺序，你只要返回 任意一种 就可以了。如果不可能完成所有课程，返回 一个空数组 。
*/
#include<bits/stdc++.h>
using namespace std;
vector<int> findOrder(int numCourses, vector<vector<int>>& prerequisites) 
{
    vector<vector<int>>tu(numCourses);//邻接表存图
    vector<int>indeg(numCourses,0);//存每个节点的入度
    for(int i=0;i<prerequisites.size();i++)
    {
        int a=prerequisites[i][0];
        int b=prerequisites[i][1];
        tu[b].push_back(a);
        indeg[a]++;
    }//建图
    vector<int>ans;//答案
    queue<int>q;
    for(int i=0;i<numCourses;i++)
    {
        if(indeg[i]==0)
        {
            q.push(i);
        }
    }
    while(!q.empty())
    {
        int num=q.front();
        q.pop();
        for(int i=0;i<tu[num].size();i++)
        {
            if(--indeg[tu[num][i]]==0)
            {
                q.push(tu[num][i]);
            }
        }
        ans.push_back(num);
    }
    if(ans.size()==numCourses)return ans;
    else return {};
}
int main()
{
    return 0;
}