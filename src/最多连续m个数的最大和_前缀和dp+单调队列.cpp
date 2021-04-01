/*
    题面：n(1e5)个数，每个数[-100,100]，取数必须连续且不超过m，问取数最大的和，要求nlogn
    来源：同学字节线上笔试
    思路：一开始想模仿LIS，用dp保持以i为末尾的结果，但是有m这个限制，实现不了。
    正确的解法：1. 求以i结尾的部分和其实等价于sum[i] - sum[head]
                2. 于是问题变成求min(sum[head])
                3. 长度为m的滑动窗口一般用单调队列来解决
    Tips：队列中只存下标，可以提升效率

    4.2 回顾： 连续的和...很明显提示前缀和了
        然后要求不超过m...很明显提示单调队列了
        单调队列需要1-n遍历，现在手里有一个当前sum[i]
        顺势可以想到不超过m，可用的范围是 sum[i-m] - sum[i-1]
        
        单调队列能把n2变成n，是因为保存了需要重复查找的部分，整个队列就是这个部分。

        给定sum[i], ans要最大， lst里面的自然越小越好，不过只能是坐标在后面的覆盖前面的，
        因为可能后面的是一个递增序列，由于pop_front操作的存在，前面的总是比后面的先消失，所以前<后并不是一个稳定的关系
        但一旦后<前，之后的都会优先选后，前就不需要了
        所以在队列清空之前，可以一直后覆盖前
        之后插入后
        之后检查前，由于存的是下标，直接和i比较即可

        这个队列保证了头一定最小(由于第一步的覆盖操作），用头更新答案
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
