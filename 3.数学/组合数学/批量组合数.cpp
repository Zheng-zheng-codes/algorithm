#include<bits/stdc++.h>
using namespace std;
const int maxm=5e4+10;
int C[maxm][maxm];
int main()
{
    for(int i=0;i<maxm;++i)
    {
        C[i][0]=C[i][i]=1;
        for(int j=1;j<i;++j)
        {
            C[i][j]=(C[i-1][j-1]+C[i-1][j])%mod;
        }
    }
}
