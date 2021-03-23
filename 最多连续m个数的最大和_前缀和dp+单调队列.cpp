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
