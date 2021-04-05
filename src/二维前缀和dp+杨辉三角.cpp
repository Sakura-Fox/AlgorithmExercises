/*
    source: https://www.luogu.com.cn/problem/P2822
    题意：有t个询问，但只有一个k，每个询问问 k|C(i,j)的数量 （i:[0,n], j:[0,min(i,m)] ）
        t 1e4 n,m 2e3 k 2-21 时间1s
    思路：
        1e4个询问，1s，只能On或者Onlogn
        观察到不同询问中有许多重叠的部分，考虑存储
        存储下来每次还是要累加，由此想到前缀和
        二维前缀和
            |
        1   |   2
            |
    -----(x1,y1)--------
            |
        3   |   4
            |           (x2,y2)
        
        显然 s(1+2+3+4) = s(1+3) + s(1+2) - s1 + S4
        dp[i][j] = s[i-1][j] + s[i][j-1] - s[i-1][j-1] + S4

        实现一
        for(int i=1;i<=2000;i++)
        {
            c[i][0] = 1;
            for(int j=1;j<=i;j++)
            {
                c[i][j] = ((c[i-1][j]%k) + (c[i-1][j-1]%k))%k;
                if(!c[i][j])ok[i][j] = 1;
            }
        }
        for(int i=2;i<=2000;i++)
        {
            for(int j=1;j<=2000;j++)
            {
                dp[i][j] = dp[i-1][j] + dp[i][j-1] - dp[i-1][j-1]; 
                dp[i][j] += ok[i][j];
            }
        }
        用了两个循环，第一个求杨辉三角，第二个前缀和
        其实可以合并
            ok[i][j]只是起了传递信息的作用
            把dp[i][j]直接放在c[i][j]里面更新是一样的
        
        实现二 见代码

        其实，考虑迅速做出来的话，两个循环的更可靠，可读性更好一点，比赛推荐先用上面那种，被卡时间了再换
*/

#include <bits/stdc++.h>
using namespace std;
#define ll long long
const int maxn = 2e3 + 5;
ll c[maxn][maxn];
ll dp[maxn][maxn];
ll t, k, n, m;
signed main()
{
    ios::sync_with_stdio(false), cin.tie(0), cout.tie(0);
    cin >> t >> k;
    c[0][0] = 1;
    for (int i = 1; i <= 2000; i++)
    {
        c[i][0] = 1;
        for (int j = 1; j <= i; j++)
        {
            c[i][j] = ((c[i - 1][j] % k) + (c[i - 1][j - 1] % k)) % k;
            dp[i][j] = dp[i-1][j] + dp[i][j-1] - dp[i-1][j-1]; 
            if(!c[i][j])
                dp[i][j]+=1;
        }
        dp[i][i+1] = dp[i][i]; 
        //关键，第i层的c[i][j]只会到c[i][i]，否则答案会错
        //但是dp的i+1层要用到dp[i][i+1]的数据，所以必须初始化
    }
    while (t--)
    {
        cin >> n >> m;
        if(m<=n)
            cout << dp[n][m] << endl;
        else cout<<dp[n][n]<<endl;
        //这里也与实现一不同，实现二j只更新到i,对于m>n的情况是未初始化状态
        //所以必须手动修正一下
        //实现二的坑点太多了，考虑比赛竞速，不如实现一
    }
}