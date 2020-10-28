/*
当后缀数组按字典序排序之后，
找到要查找的l1开始的后缀的排名，
那么可能和l1-r1相等的字符串的起始位置的后缀的排名
应该在以l1开始的后缀左右。
通过二分查找到lcp(最长相等前缀)>=len的位置，
然后该区间内的后缀的起始位置在[l2,r2-(r1-l1)]之间的个数就是答案。
*/

#pragma GCC optimize(2)
#include <bits/stdc++.h>
#include <cstdio>
#include <string>
#include <queue>
#include <cstring>
#include <iostream>
using namespace std;
//mt19937 rnd(time(NULL));
#define pp pair<int, int>
#define ull unsigned long long
#define ls root << 1
#define rs root << 1 | 1
//#define int long long
typedef long long ll;
const int inf = 1e9+7;
const int NINF = 0xc0c0c0c0;
const int maxn = 1e5 + 7;
const int bas = maxn / 2;
const int Maxn = 1e7 + 7;
const double eps = 1e-10;
const ll mod = 1e9+7;
template <typename T> void read(T &x){
    x=0;
    char c=getchar();
    //if(c==EOF)return false;
    T flag=1;
    while(c<'0' || c>'9'){
        if(c=='-')
            flag=-1;
        c=getchar();
    }
    while(c>='0' && c<='9'){
        x=x*10+c-'0';
        c=getchar();
    }
    x=x*flag;
    //return true;
}
char s[maxn];
struct SA{
    static const int maxn = 1e5+7;
    int h[maxn],sa[maxn],rk[maxn],tax[maxn],tp[maxn],m;
    void Rsort(int n){
        for(int i=1;i<=m;i++) tax[i]=0;
        for(int i=1;i<=n;i++) tax[rk[tp[i]]]++;
        for(int i=1;i<=m;i++) tax[i]+=tax[i-1];
        for(int i=n;i;i--) sa[tax[rk[tp[i]]]--]=tp[i];
    }
    void build(int n){
        for(int i=1;i<=n;i++) rk[i]=s[i],tp[i]=i;
        m=128,Rsort(n);

        for(int w = 1, p = 1, i;p < n; w += w, m = p){
            for(p = 0, i = n - w + 1; i <= n; i++){
                tp[++p]=i;
            }
            for(int i = 1;i <= n;i ++) if(sa[i] > w) tp[++p] = sa[i] - w;
            Rsort(n);swap(rk,tp);rk[sa[1]] = p = 1;
            for(int i = 2;i <= n;i++){
                rk[sa[i]] = (tp[sa[i - 1]] == tp[sa[i]] && tp[sa[i - 1] + w] == tp[sa[i] + w])?p: ++p;
            }
        }
        int j,k=0;
        for(int i=1;i<=n;h[rk[i++]]=k){
            for(k = k? k-1:k,j=sa[rk[i]-1];k<=n && s[i+k] == s[j+k]; ++k);
        }
    }
    void print(int n){
        for(int i=1;i<=n;i++){
            cout<<sa[i]<<' ';
        }
        puts("");
    }
}sa;
struct Rmq{
    static const int maxn = 1e5+7;
    int st[maxn][20];
    int lg[maxn];
    void init(int n){
        for(int i=1;i<=n;i++){
            st[i][0]=sa.h[i];
        }
        for(int i=2;i<=n;i++) lg[i] = lg[i>>1] + 1;
        st[1][0]=(n-sa.sa[1]+1);
        for(int i=1;(1<<i)<=n;i++){
            for(int j=1;j+(1<<i)-1<=n;j++){
                st[j][i]=min(st[j][i-1],st[j+(1<<(i-1))][i-1]);
            }
        }
    }
    void print(int n){
        for(int i=1;i<=n;i++){
            cout<<st[i][0]<<' ';
        }
        puts("");
    }
    int ask(int l,int r){
        if(l==r)swap(l,r);l++;
        if(l>r)return 0;
//        cout<<l<<' '<<r<<endl;
        int k=lg[r-l+1];
        //cout<<l<<' '<<r<<' '<<min(st[l][k],st[r-(1<<k)+1][k])<<endl;
        return min(st[l][k],st[r-(1<<k)+1][k]);
    }
}rmq;
struct seg_tree{
    static const int maxn = 1e5+7;
    struct tree{
        int ll,rr,sum;
    }t[maxn<<5];
    int head[maxn],cnt;
    void update(int pre,int &rt,int l,int r,int k){
        t[rt=++cnt]=t[pre];
        t[rt].sum++;
        if(l==r)return ;
        int mid=l+r>>1;
        if(mid>=k) update(t[pre].ll,t[rt].ll,l,mid,k);
        else update(t[pre].rr,t[rt].rr,mid+1,r,k);
    }
    int query(int pre,int rt,int l,int r,int k){
        if(k<1) return 0;
        if(l==r)return t[rt].sum-t[pre].sum;
        int mid=l+r>>1,sum=0;
        if(mid>=k) sum=query(t[pre].ll,t[rt].ll,l,mid,k);
        else sum=t[t[rt].ll].sum-t[t[pre].ll].sum+query(t[pre].rr,t[rt].rr,mid+1,r,k);
        return sum;
    }
}seg;
int get_l(int x,int len){
    int l=1,r=x,ans=x;
    while(l<=r){
        int mid=l+r>>1;
        if(rmq.ask(mid,x)>=len) r=mid-1,ans=mid;
        else l=mid+1;
        //puts("l");
    }
    //puts("returnl");
    return ans;
}
int get_r(int x,int len,int n){
    int l=x,r=n,ans=x;
    while(l<=r){
        int mid=l+r>>1;
        if(rmq.ask(x,mid)>=len || mid==x) l=mid+1,ans=mid;
        else r=mid-1;
        //puts("r");
    }
    //puts("returnr");
    return ans;
}
void solve() {
    int n;
    read(n);
    scanf("%s",s+1);
    sa.build(n);
//    sa.print(n);
    rmq.init(n);
    //rmq.print(n);
    for(int i=1;i<=n;i++) seg.update(seg.head[i-1],seg.head[i],1,n,sa.sa[i]);
    int q;
    read(q);
    int l1,r1,l2,r2;
    while(q--){
        l1,r1,l2,r2;
        read(l1),read(r1),read(l2),read(r2);
        if(r1-l1>r2-l2){puts("0");continue;}
        int l=get_l(sa.rk[l1],r1-l1+1),r=get_r(sa.rk[l1],r1-l1+1,n);
        int ansl=seg.query(seg.head[l-1],seg.head[r],1,n,l2-1),ansr=seg.query(seg.head[l-1],seg.head[r],1,n,r2-(r1-l1+1)+1);
        cout<<ansr-ansl<<'\n';
    }
}
signed main() {
#ifndef ONLINE_JUDGE
    freopen("in.in","r",stdin);
    //freopen("out.out","w",stdout);
#endif
    int T = 1;
    //scanf("%d",&T);
    while (T--) solve();
#ifndef ONLINE_JUDGE
    cerr<<"Time elapsed: "<<1.0*clock()/CLOCKS_PER_SEC << "s.\n";
#endif
}