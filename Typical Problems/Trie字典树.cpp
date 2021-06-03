/*
    source: https://icpcarchive.ecs.baylor.edu/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=1943
    题意： 多组数据，每组一开始给你一个string s,然后给你一个规模为n的字典{s1,s2,...sn}
    问多少种方式用字典内的数组合为s，答案模mod
    思路： 建立字典树，dp[i]表示第i个开始到末尾的子串的答案, i从后往前遍历，i里面循环j，查字典树，每查到一个词就+=dp[j+1]
    注意要dp[n] = 1

    p.s. 一开始用struct/class存Trie树，这是动态存储，存在栈里面，win的栈大小默认2MB, linux默认8MB
    这题4e5*27*4 约4MB，超了，跑不了，遂改用全局的静态存储
    不知cpp有没有static类这种实现，挖个坑
*/
#include <bits/stdc++.h>
using namespace std;
const int maxnode = 4e5 + 5; //树的节点数，等价于单词的最大长度
const int sigma_size = 26;   //字母表的大小
const int mod = 20071027;
/*
    根节点编号为0
    ch[i][0..26] 存储第i个节点在0..26有无子结点，
        有则存储子结点的编号，无则为0（这不会与根节点冲突，因为根节点不为任何节点的子结点）
    val[i] 存储第i个节点的属性，在这个问题里，为“是否为单词节点”， 在其他问题里可以是权值等。
    sz即size，当前存储的节点的数量
    函数fidx 返回 字母对应的编号 比如小写英文字母 a-z == 0-26
*/
int ch[maxnode][sigma_size];
bool val[maxnode];
int sz;
void init()
{
    sz = 1;
    memset(ch[0], 0, sizeof ch[0]); //初始化根节点
    val[0] = 0;
}
int fidx(char c) { return c - 'a'; }
void insert(string s)
{
    int u = 0;
    for (int i = 0; i < s.size(); i++)
    {
        int c = fidx(s[i]);
        if (!ch[u][c])
        {
            memset(ch[sz], 0, sizeof ch[sz]);
            val[sz] = 0;
            ch[u][c] = sz++;
        }
        u = ch[u][c];
    }
    val[u] = 1;
}
const int maxn = 3e5 + 5;
int dp[maxn]; //dp[i] 代表 s[i-s.size()]的后缀字符串的答案数
string s;
signed main()
{
    ios::sync_with_stdio(false), cin.tie(0), cout.tie(0);
    int cnt = 0;
    while (cin >> s)
    {
        cnt++;
        init();
        int n;
        cin >> n;
        string wd;
        while (n--)
        {
            cin >> wd;
            insert(wd);
        }
        n = s.size();
        memset(dp, 0, sizeof dp);
        dp[n] = 1;
        for (int i = n - 1; i >= 0; i--)
        {
            int u = 0;
            for (int j = i; j < n; j++)
            {
                int c = fidx(s[j]);
                if (ch[u][c])
                {
                    u = ch[u][c];
                    if (val[u])
                        dp[i] += dp[j + 1], dp[i] %= mod;
                }
                else
                    break;
            }
        }
        cout << "Case " << cnt << ": " << dp[0] << endl;
    }
}