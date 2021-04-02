/*
    source: https://www.luogu.com.cn/problem/P5858
    题意： n个点(a[1-n])依次入队，队列长度限制为w，每次入队时可弹出[0,s]个数，
    弹出谁没有关系因为只看队列长度，每个点对答案的贡献为那个点入队后，队列长度*a[i]
    求最大贡献
    思路1： 直接dp，dp的参数由题意决定：
        顺序进入 —— i为点的序号
        贡献为当前队列长度*a[i], a[i]可以快速索引到但长度不行 — j为当前队列长度
        累加答案，最后输出最后一层最大的，这样路径已隐含在dp值中
        // dp[i][j] = max{dp[i-1][k] + j*a[i]}
        // j == k - t + 1; 1 <= j,k <= w; 0 <= t <= s
        // k == j+t-1  max(1,j-1)<= k <= min(j+s-1,w)
        考虑到初始化，k>=j-1即可（手动调出来的）

        很遗憾，复杂度n2w约为n3, 数据规模5e3，过不了，至少要n2才行

    思路2： 第一层循环遍历i的不可能取消，考虑从内层n2优化成n
            题面很明显地指向单调队列（长度为w的滑动窗口），只是要考虑怎么用
            首先dp式，把常量提出来优化
                dp[i][j] = max{dp[i-1][k]} + j*a[i]
            观察思路一的代码
                随着j++, k的起始位置每次加一，结束位置每次加一直到碰到w为止
                明显的单调队列，每次加一个进来，pop一个出去
            list<int> lst;
            lst.push_back(0); //存dp[i-1][j]的j
            int j=1;
            for(int k=1;k<=w;k++)
            {
                while(!lst.empty()&&dp[i-1][lst.back()]<dp[i-1][k])lst.pop_back();
                lst.push_back(k);
                while(!lst.empty()&&j-lst.front()>1)lst.pop_front();
                if(k>=s)dp[i][j+1] = dp[i-1][lst.front()] + j*a[i];
                j++;
            }
            while(j<=w)
            {
                dp[i][j+1] = dp[i-1][lst.front()] + j*a[i];
                j++;
            }

            还是错误，第一是必须j*(ll)a[i]，否则会溢出
            修正后大部分ac，少量tle，被卡了100ms

            猜想stl的list效率问题，改用数组实现
            list 0.6s tle
            数组 0.1s ac
*/

#include <bits/stdc++.h>
using namespace std;
#define ll long long
const int maxn = 5e3 + 5;
int a[maxn];
//遍历到第i个点,当前队列j个数（包含当前），累加的答案
ll dp[maxn][maxn];
int q[maxn];
// dp[i][j] = max{dp[i-1][k] + j*a[i]}
// j == k - t + 1; 1 <= j,k <= w; 0 <= t <= s
// k == j+t-1  max(1,j-1)<= k <= min(j+s-1,w)
signed main()
{
    ios::sync_with_stdio(false), cin.tie(0), cout.tie(0);
    int n, w, s;
    cin >> n >> w >> s;
    memset(dp, 0x8f, sizeof dp);
    for (int i = 1; i <= n; i++)
        cin >> a[i];
    dp[0][0] = 0;
    for (int i = 1; i <= n; i++)
    {
        // list<int> lst;
        // lst.push_back(0); //存dp[i-1][j]的j
        // int j = 1;
        // for (int k = 1; k <= w; k++) //如何保证 k<=j+s-1? k==s j==1 k++ j++ k-j==s-1
        // {
        //     while (!lst.empty() && dp[i - 1][lst.back()] <= dp[i - 1][k])
        //         lst.pop_back();
        //     lst.push_back(k);
        //     while (!lst.empty() && j - lst.front() > 1)
        //         lst.pop_front();
        //     if (k >= s)
        //     {
        //         dp[i][j] = dp[i - 1][lst.front()] + j * (ll)a[i];
        //         j++;
        //     } 
        // }
        // while (j <= w) //k不变 j++ k-j<=s-1
        // {
        //     while (!lst.empty() && j - lst.front() > 1)
        //         lst.pop_front();
        //     dp[i][j] = dp[i - 1][lst.front()] + j *(ll) a[i];
        //     j++;
        // }
        int l = 1, r = 1;
        q[l] = 0;
        int j = 1;
        for(int k=1;k<=w;k++)
        {
            while(l<=r&&dp[i-1][q[r]]<=dp[i-1][k])
                r--;
            q[++r] = k;
            while(l<=r&&j-q[l]>1)
                l++;
            if(k>=s){
                dp[i][j] = dp[i-1][q[l]] + j *(ll) a[i];
                j++;
            }
        }
        while(j<=w)
        {
            while(l<=r&&j-q[l]>1)
                l++;
            dp[i][j] = dp[i-1][q[l]] + j *(ll) a[i];
            j++;
        }
    }
    ll ans = 0x8f8f8f8f8f8f8f8f;
    for (int i = 1; i <= w; i++)
        ans = max(ans, dp[n][i]);
    cout << ans << endl;
}

// #include<bits/stdc++.h>
// using namespace std;
// #define ll long long
// const int maxn = 5e3+5;
// int a[maxn];
// //遍历到第i个点,当前队列j个数（包含当前），累加的答案
// ll dp[maxn][maxn];
// // dp[i][j] = max{dp[i-1][k] + j*a[i]}
// // j == k - t + 1; 1 <= j,k <= w; 0 <= t <= s
// // k == j+t-1  max(1,j-1)<= k <= min(j+s-1,w)
// signed main()
// {
//     ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
//     int n,w,s;cin>>n>>w>>s;
//     memset(dp,0x8f,sizeof dp);
//     for(int i=1;i<=n;i++)
//         cin>>a[i];
//     dp[0][0] = 0;
//     for(int i=1;i<=n;i++)
//     {
//         for(int j=1;j<=w;j++)
//         {
//             for(int k = j-1; k<= min(j+s-1,w);k++)
//                 dp[i][j] = max(dp[i][j], dp[i-1][k] + j*(ll)a[i]);
//             //cout<<dp[i][j]<<" ";
//         }
//         //cout<<endl;
//     }
//     ll ans = 0x8f8f8f8f8f8f8f8f;
//     for(int i=1;i<=w;i++)
//         ans = max(ans,dp[n][i]);
//     cout<<ans<<endl;
// }