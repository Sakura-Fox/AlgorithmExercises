/*
    一道对思维有启发的贪心
    题本身不难，愿意去猜的话可以猜到
    source: https://vjudge.net/problem/UVA-11729
    题意： n个人做事，每个人你需要花Bi分钟交代任务，随后他花Ji分钟自己去做
    交代完一个人后你会去找下一个交代任务，手下做事是并行的
    思路： 现实中也很常见的问题， 直接建立模型吧： 优先选Ji大的，即工作时间长的
    问就是math
        注意这个思维：其他不动，取两个相邻任务出来，证明两个中Ji大的应该先走
        定义任务 （B1，J1），（B2，J2） 其中 J1 >= J2，即工作时间长的那个为任务1
        无非谁先走
            1先走 time1 = B1 + max(J1,B2+J2)
            2先走 time2 = B2 + B1 + J1 >= time1 (J1>=J2)
        所以无论怎样1先走都最优
*/

#include<bits/stdc++.h>
using namespace std;
int n;
const int maxn = 1e3+5;
struct node
{
    int b,j;
    bool operator<(node& rhs)
    {
        return j>rhs.j;
    }
}nodes[maxn];
signed main()
{
    ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
    int cnt = 0;
    while(cin>>n&&n)
    {
        cnt++;
        for(int i=0;i<n;i++)
            cin>>nodes[i].b>>nodes[i].j;
        sort(nodes,nodes+n);
        int srt = 0,end = 0;
        for(int i=0;i<n;i++)
        {
            srt+=nodes[i].b;
            end = max(end,srt+nodes[i].j);
        }
        cout<<"Case "<<cnt<<": "<<end<<endl;
    }
}