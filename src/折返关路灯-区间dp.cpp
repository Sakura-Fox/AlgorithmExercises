/*
    source: https://www.luogu.com.cn/problem/P1220
    题意： 一条街 n个路灯 每盏路灯有一个功率值val[i]
            从第c个路灯出发开始关路灯，行进速度恒为1，问关完所浪费的最小val和
            （要考虑时间流逝 路灯只要没关 就会贡献 val*持续时间）
    思路： dfs 每个点有左右两个方向，至少我不知道怎么处理环的问题
            贪心 不可行
            dp n<=50 暗示高维dp
            首先有两个结论：
                1. 经过一个灯立即熄灭是最优的（显然）
                2. 对于一个下标区间，熄灭这一下标区间，时间最短，
                最后必定停在左端或者右端
                （由结论1可证，若不在，则改点必定在一个端点与起始点之间，违反1）
                
            以后遇到坐标轴上的可以考虑区间dp
            dp[i][j] 为 关完[i,j]路灯这一时刻，所浪费的功
            考虑转移，无非是dp[i+1][j]或dp[i][j-1]转过来的
            但是区间关完这一时刻，如上文，有两个可能坐标，所以加一个bool维度
            dp[i][j][0] 表示停在i
            dp[i][j][1] 表示停在j

        def
        int cal(int i,int j,int l,int r)
        {
            //i,j 表示转移的起始下标（方向不重要）用于计算时间
            //l,r 表示转移前的已熄灭区间dp[l][r] 用于计算功率和（用前缀和）
            return (loc[j]-loc[i])*(sum[n]-sum[r]+sum[l-1]);
        }      
    转移方程
    dp[i][j][0] = min(
        dp[i+1][j][0] + cal(i,i+1,i+1,j), dp[i+1][j][1] + cal(i,j,i+1,j)
    );      
    dp[i][j][1] = min(
        dp[i][j-1][0] + cal(i,j,i,j-1), dp[i][j-1][1] + cal(j-1,j,i,j-1)
    );
    dp[c][c][0] = dp[c][c][1] = 0;
    可以看到，必须从c开始拓展
    i+1 -> i i是逆序，且根据题意 i<=c i是逆序从c开始拓展
    j-1 -> j j是顺序，且根据题意 j>=c j是顺序从c开始拓展

    for(int i=c;i>0;i--)
    {
        for(int j=c;j<=n;j++)
        {
            if(i==j)continue;
            dp[i][j][0] = min(
                dp[i+1][j][0] + cal(i,i+1,i+1,j), dp[i+1][j][1] + cal(i,j,i+1,j)
            );      
            dp[i][j][1] = min(
                dp[i][j-1][0] + cal(i,j,i,j-1), dp[i][j-1][1] + cal(j-1,j,i,j-1)
            );
        }
    }
    为了保证错误的区间和端点不被取，初始化dp为0x3f3f3f3f
*/

#include <bits/stdc++.h>
using namespace std;
const int maxn = 55;
int n, c;
int loc[maxn];
int sum[maxn];
int dp[maxn][maxn][2];
int cal(int i, int j, int l, int r)
{
    //i,j 表示转移的起始下标（方向不重要）用于计算时间
    //l,r 表示转移前的已熄灭区间dp[l][r] 用于计算功率和（用前缀和）
    return (loc[j] - loc[i]) * (sum[n] - sum[r] + sum[l - 1]);
}
signed main()
{
    ios::sync_with_stdio(false), cin.tie(0), cout.tie(0);
    cin >> n >> c;
    memset(dp,0x3f,sizeof dp);
    dp[c][c][0] = dp[c][c][1] = 0;
    for (int i = 1; i <= n; i++)
    {
        cin >> loc[i] >> sum[i];
        sum[i] += sum[i - 1];
    }
    for(int i=c;i>0;i--)
    {
        for(int j=c;j<=n;j++)
        {
            if(i==j)continue;
            dp[i][j][0] = min(
                dp[i+1][j][0] + cal(i,i+1,i+1,j), dp[i+1][j][1] + cal(i,j,i+1,j)
            );      
            dp[i][j][1] = min(
                dp[i][j-1][0] + cal(i,j,i,j-1), dp[i][j-1][1] + cal(j-1,j,i,j-1)
            );
        }
    }
    cout<<min(dp[1][n][0],dp[1][n][1])<<endl;
}