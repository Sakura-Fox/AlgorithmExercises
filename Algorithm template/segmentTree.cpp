//segment tree
#define lson rt<<1
#define rson rt<<1|1
#define mid l+((r-l)>>1)
const int maxn = 1e5+5;
int sum[maxn<<2];
inline void pushup(int rt){sum[rt]=sum[lson]+sum[rson];}
void build(int l,int r,int rt){
    if(l==r){
        sum[rt]=1;
        return;
    }
    build(l,mid,lson);
    build(mid+1,r,rson);
    pushup(rt);
}
void updateTree(int l,int r,int rt,int val,int pos){
    if(l==r){
        sum[rt] = val;
        return;
    }
    if(pos<=mid)updateTree(l,mid,lson,val,pos);
    else updateTree(mid+1,r,rson,val,pos);
    pushup(rt);
}
int query(int l,int r,int rt,int L,int R){
    if(R<L)return 0;
    if(L<=l&&r<=R)
        return sum[rt];
    int ans = 0;
    if(L<=mid)ans+=query(l,mid,lson,L,R);
    if(R>mid)ans+=query(mid+1,r,rson,L,R);
    return ans;
}