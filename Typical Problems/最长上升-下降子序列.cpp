/*
    source: https://www.luogu.com.cn/problem/P1091
    题意： 1e2的数据求最长上升-下降子序列（顶点可以为首/尾）
    思路1： for三遍，一遍lis，一遍lds，一遍max，复杂度n2
    思路2： lis的nlogn求法 
            dp1保存长度为i的lis的最小末尾值，用lower_bound找到idx， lis[cur] = idx;
            lds类推
            最后on合并求max
*/

#include<bits/stdc++.h>
using namespace std;
const int maxn = 1e3+5;
int n;
int a[maxn];
int dp1[maxn], dp2[maxn]; //长度为i的lis的最小末尾值， 长度为i的lds的最小起始值
int lis[maxn], lds[maxn];
// nlogn 解法
signed main()
{
    ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
    cin>>n;
    for(int i=1;i<=n;i++)
        cin>>a[i];
    dp1[1] = a[1], dp2[1] = a[n];
    lis[1] = 1, lds[n] = 1;
    int len1 = 1, len2 = 1;
    for(int i=2;i<=n;i++)
    {
        int* p = lower_bound(dp1+1,dp1+1+len1,a[i]);
        int dis = distance(dp1+1,p);
        if(dis==len1)
            dp1[++len1] = a[i];
        else
            dp1[1+dis] = a[i];
        lis[i] = dis+1;
    }
    for(int i=n-1;i>0;i--)
    {
        int* p = lower_bound(dp2+1,dp2+1+len2,a[i]);
        int dis = distance(dp2+1,p);
        if(dis==len2)
            dp2[++len2] = a[i];
        else 
            dp2[1+dis] = a[i];
        lds[i] = dis+1;
    }
    int ans = 0;
    for(int i=1;i<=n;i++)
        ans = max(ans,lis[i]+lds[i]);
    cout<<n-ans+1<<endl;
}

// n2 解法
// signed main()
// {
//     ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
//     cin>>n;
//     for(int i=1;i<=n;i++)
//         cin>>a[i];
//     for(int i=1;i<=n;i++)
//     {
//         for(int j=0;j<i;j++)
//         {
//             if(a[i]>a[j])
//                 lis[i] = max(lis[i],lis[j]+1);
//         }
//     }
//     for(int i=n;i>0;i--)
//     {
//         for(int j=n+1;j>i;j--)
//         {
//             if(a[i]>a[j])
//                 lds[i] = max(lds[i],lds[j]+1);
//         }
//     }
//     int ans = 0;
//     for(int i=1;i<=n;i++)
//     {
//         ans = max(ans,lis[i]+lds[i]);
//     }
//     cout<<n-ans+1<<endl;
// }