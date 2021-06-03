/*
    source: https://www.luogu.com.cn/problem/P1077
    题意：给n个数 [a1,a2,...,an], 每个数可取[0,ai], 取出累加得m
            问共多少种方案
    思路：
        若模拟每种花取遍[0,ai], 复杂度n^n，不行
        考虑到 0+2 和 1+1 之后的搜索路径一模一样
        考虑在每一层（每种花）收束再搜索
        实际实现是从结果开始迭代寻找
        每层寻找后更新值（收束）
        复杂度nm
*/
#include <bits/stdc++.h>
using namespace std;
const int maxn = 1e3;
int a[maxn];
int dp[maxn][maxn]; //第i个数，累积到j 的方案数
int n, m;
const int mod = 1e6 + 7;
int f(int cur,int sum)
{
    if(cur==0)
        return dp[0][sum] = sum<=a[0];
    if(dp[cur][sum])
        return dp[cur][sum];
    int ans = 0;
    for(int i=0;i<=a[cur]&&i<=sum;i++)
    {
        ans += f(cur-1,sum-i);
        ans %= mod;
    }
    return dp[cur][sum] = ans;
}
signed main()
{
    ios::sync_with_stdio(false), cin.tie(0), cout.tie(0);
    cin >> n >> m;
    for (int i = 0; i < n; i++)
    {
        cin >> a[i];
    }
    cout<<f(n-1,m)<<endl;
}