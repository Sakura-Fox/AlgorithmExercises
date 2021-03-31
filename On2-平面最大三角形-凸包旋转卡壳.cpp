/*
    source: https://vjudge.net/contest/424589#problem/A
    
    -----实际数据大于1e5,远大于题目给出的5e3-----
    -----调了2h，真搞人心态-----

    题意： 平面n个点，n2求最大三角形
    思路：
        可证 最大三角形一定在凸包上
        然后 旋转卡壳
        即 遍历i和j，ptr只增不减（由凸包性质决定)
*/
#include <bits/stdc++.h>
using namespace std;
#define int long long
const double eps = 1e-10;
struct Point{
    int x,y;
    Point(int x=0, int y=0):x(x),y(y){}
};
typedef Point Vector;
Vector operator+ (Vector A, Vector B){return Vector(A.x+B.x, A.y+B.y);}
Vector operator- (Point A, Point B){return Vector(A.x-B.x, A.y-B.y);}
Vector operator* (Vector A, double p){return Vector(A.x*p,A.y*p);}
Vector operator/ (Vector A, double p){return Vector(A.x/p, A.y/p);}
bool operator< (const Point& a, const Point& b){
    return a.x<b.x||(a.x==b.x&&a.y<b.y);
}
int dcmp(double x){
    if(fabs(x)<eps)return 0;
    else return x<0?-1:1;
}
bool operator== (const Point& a, const Point& b){
   return dcmp(a.x-b.x)==0 && dcmp(a.y-b.y)==0;
}
double Dot(Vector A, Vector B){return A.x*B.x + A.y*B.y;}
double Length(Vector A){ return sqrt(Dot(A,A));}
double Angle(Vector A, Vector B){return acos( Dot(A,B)/Length(A)/Length(B) ); }
int Cross(Vector A, Vector B){return A.x*B.y - A.y*B.x;}
int Area2(Point A, Point B, Point C){return Cross(B-A,C-A);}
/*
    输入点数组p，个数为n，输出点数组ch，返回凸包顶点数
    函数执行完后输入点顺序被破坏
    凸包边上  有点用<  无点用<=
*/
int ConvexHull(Point* p, int n, Point* ch)
{
    sort(p,p+n);
    n = unique(p,p+n)-p;
    int m = 0; //current ch idx
    for(int i=0;i<n;i++){
        while(m>1&& Cross(ch[m-1]-ch[m-2],p[i]-ch[m-2])<0 )m--;
        ch[m++] = p[i];
    }
    int k = m; //保存k为下半凸包的最后一个(即(xmax,ymax))的idx+1
    for(int i=n-2;i>=0;i--){
        while(m>k&& Cross(ch[m-1]-ch[m-2],p[i]-ch[m-2])<0 )m--;
        ch[m++] = p[i];
    }
    if(n>1)m--; //除了n==1外，其他情况都要走第二个循环，第一个点(xmin,ymin)被添加了两次，要删去
    return m;
}
const int maxn = 1e6+5;
Point p[maxn],ch[maxn];
signed main()
{
    ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
    int n;cin>>n;
    for(int i=0;i<n;i++)
        cin>>p[i].x>>p[i].y;
    n = ConvexHull(p,n,ch);
    int ans = 0;
    for(int i=0;i<n;i++)
    {
        int j = i+1;
        int ptr = j+1;
        for(;j<n;j++)
        {
            while(ptr<n-1 && Area2(ch[i],ch[j],ch[ptr])
            <Area2(ch[i],ch[j],ch[ptr+1]) )ptr++;
            ans = max(ans,Area2(ch[i],ch[j],ch[ptr]));
        }
    }
    cout<<fixed<<setprecision(7)<<(double)ans/2<<endl;
}