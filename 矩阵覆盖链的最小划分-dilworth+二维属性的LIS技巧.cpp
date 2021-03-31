/*
    source: https://www.luogu.com.cn/problem/P1233
    题意： 
        两个矩形A和B, A.x>=B.x&&A.y>=B.y 则A可覆盖B
        给你一堆矩形，求覆盖链的最小划分数
    思路：
        链的最小划分数 等价于 最长反链长度 (dilworth)
        问题变成：适当重排数据，使得可从其中获取最优解，然后LIS

        重排要使得
            -----所有比矩形B大的矩形A，都必须在B的前面-----
        bool cmp(node a,node b)
        {return a.x>b.x||(a.x==b.x&&a.y>b.y);}
        显然可以实现
        
        之后求LIS nlogn
        dp[i] //长度为i的子序列的最小末尾
        lower_bound一下，找不到则入队，找到则覆盖（贪心）
        最后输出队列长度
*/
#include <bits/stdc++.h>
using namespace std;
const int maxn = 1e4+5;
struct node
{
    int x,y;
    bool operator<(node& rhs)
    {
        return x>rhs.x || (x==rhs.x&&y>rhs.y);
    }
}nodes[maxn];
int dp[maxn]; //长度为i的子序列的最小末尾
signed main()
{
    ios::sync_with_stdio(false), cin.tie(0), cout.tie(0);
    int n;cin>>n;
    for(int i=1;i<=n;i++)
        cin>>nodes[i].x>>nodes[i].y;
    sort(nodes+1,nodes+1+n);
    dp[1] = nodes[1].y;
    int len = 1;
    for(int i=2;i<=n;i++)
    {
        int* p = lower_bound(dp+1,dp+1+len,nodes[i].y);
        int dis = distance(dp+1,p);
        if(dis==len)
            dp[++len] = nodes[i].y;
        else dp[1+dis] = nodes[i].y;
    }
    cout<<len<<endl;
}