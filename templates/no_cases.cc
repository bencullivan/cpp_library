#include <bits/stdc++.h>
#define GREEN "\033[32m"
#define MAGENTA "\033[35m"
#define RESET "\033[0m"
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
#define pb push_back
#define fi first
#define se second
#define all(x) begin(x),end(x)
#define sz(x) (int)(x).size()
#ifdef LOL_DEBUG
#define tcT template<typename T
tcT,typename U> ostream& operator<<(ostream& os,const pair<T,U>& p) {return os<<"("<<p.first<<", "<<p.second<<")";}
tcT,typename U=typename enable_if<!is_same<T,string>::value,typename T::value_type>::type> ostream& operator<<(ostream &os,const T &v)
{os<<"\n{";string sep;for(const U &x:v)os<<sep<<x,sep=", ";return os<<'}';}
void debug_help() {cout<<RESET<<endl;}
tcT,typename... U> void debug_help(T t,U... u) {cout<<t;if(sizeof...(u))cout<<", ";debug_help(u...);}
int debug_dms[10],debug_md;
void debug_fill() {}
tcT,typename... U> void debug_fill(T t,U... u) {debug_dms[debug_md++]=t;debug_fill(u...);}
tcT> void debug_arr(T x,int d) {cout<<x;}
tcT> void debug_arr(T* arr,int d)
{cout<<"\n{";string sep;for(int i=0;i<debug_dms[d];i++)cout<<sep,sep=", ",debug_arr(arr[i],d+1);cout<<'}';if(d==0)cout<<RESET<<endl;}
#define dbg(...) cout<<MAGENTA<<__LINE__<<" ["<<#__VA_ARGS__<<"]: "<<GREEN,debug_help(__VA_ARGS__)
#define dba(arr,...) cout<<MAGENTA<<__LINE__<<" ["<<#arr<<"]: "<<GREEN,debug_md=0,debug_fill(__VA_ARGS__),debug_arr(arr,0)
#else
#define dbg(...)
#define dba(arr,...)
#endif
const char df = '\n';

void solve() {
}

signed main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  int tt = 1;
  //cin >> tt;
  for (int i = 1; i <= tt; i++) {
    solve();
  }
  return 0;
}
