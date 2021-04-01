/*
    题面：n(1e5)个数，每个数[-100,100]，取数必须连续且不超过m，问取数最大的和，要求nlogn
    来源：同学字节线上笔试
    思路：一开始想模仿LIS，用dp保持以i为末尾的结果，但是有m这个限制，实现不了。
    正确的解法：1. 求以i结尾的部分和其实等价于sum[i] - sum[head]
                2. 于是问题变成求min(sum[head])
                3. 长度为m的滑动窗口一般用单调队列来解决
    Tips：队列中只存下标，可以提升效率
*/
#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int maxn = 1e5+5;
int sum[maxn];
signed main()
{
    ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
    int n,m;cin>>n>>m;
    for(int i=1;i<=n;i++)
    {
        cin>>sum[i];
        sum[i]+=sum[i-1];
    }
    list<int> lst;
    lst.push_back(1);
    int ans = sum[1];
    for(int i=2;i<=n;i++)
    {
        while(!lst.empty()&&sum[lst.back()]>sum[i])lst.pop_back();
        lst.push_back(i);
        while(!lst.empty()&&i-lst.front()>m)lst.pop_front();
        ans = max(ans,sum[i]-sum[lst.front()]);
    }
    cout<<ans<<endl;
}
