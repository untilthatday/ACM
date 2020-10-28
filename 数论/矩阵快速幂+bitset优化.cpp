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
int n;
struct mul{
    bitset<600>a[600];
    bitset<600>c[600];
    mul(){
        for(int i=1;i<=n;i++)a[i].reset(),c[i].reset();
    }
    mul friend operator * (mul x,mul y){
        mul tmp;
        for(int i=1;i<=n;i++){
            for(int j=1;j<=n;j++){
                tmp.a[i][j]=(x.a[i]&y.c[j]).any();
                tmp.c[i][j]=(x.a[j]&y.c[i]).any();
            }
        }
        return tmp;
    }
    void init(){
        for(int i=1;i<=n;i++)a[i].set();
    }
    void print(){
        for(int i=1;i<=n;i++){
            for(int j=1;j<=n;j++){
                cout<<a[i][j]<<' ';
            }
            puts("");
        }
    }
};
mul qui_(mul n,ll m){
    mul ans;
    ans=n;
    m--;
    //cout<<m<<endl;
    while(m){
        //puts("n:");
        //n.print();
        if(m&1)ans=ans*n;//puts("ans:"),ans.print();
        n=n*n;
        m>>=1;
    }
    return ans;
}
void solve() {
    int s,t;
    ll o;
    cin>>n>>s>>t>>o;
    int m;
    read(m);
    mul a;
    for(int i=1;i<=m;i++){
        int u,v;
        read(u),read(v);
        a.a[u][v]=1;
        a.c[v][u]=1;
    }
    //a.print();
    a=qui_(a,o);
//    for(int i=1;i<=n;i++){
//        for(int j=1;j<=n;j++){
//            cout<<a.a[i][j]<<' ';
//        }
//        puts("");
//    }
   // a.print();
    if(a.a[s][t]==1)puts("They call me Prophet");
    else puts("Remember me");
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