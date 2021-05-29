#include <bits/stdc++.h>
#define green "\033[32m"
#define magenta "\033[35m"
#define reset "\033[0m"
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
#ifdef lol_debug
#define tct template<typename t
tct,typename u> ostream& operator<<(ostream& os,const pair<t,u>& p) {return os<<"("<<p.first<<", "<<p.second<<")";}
tct,typename u=typename enable_if<!is_same<t,string>::value,typename t::value_type>::type> ostream& operator<<(ostream &os,const t &v)
{os<<"\n{";string sep;for(const u &x:v)os<<sep<<x,sep=", ";return os<<'}';}
void debug_help() {cout<<reset<<endl;}
tct,typename... u> void debug_help(t t,u... u) {cout<<t;if(sizeof...(u))cout<<", ";debug_help(u...);}
int debug_dms[10],debug_md;
void debug_fill() {}
tct,typename... u> void debug_fill(t t,u... u) {debug_dms[debug_md++]=t;debug_fill(u...);}
tct> void debug_arr(t x,int d) {cout<<x;}
tct> void debug_arr(t* arr,int d)
{cout<<"\n{";string sep;for(int i=0;i<debug_dms[d];i++)cout<<sep,sep=", ",debug_arr(arr[i],d+1);cout<<'}';if(d==0)cout<<reset<<endl;}
#define dbg(...) cout<<magenta<<__line__<<" ["<<#__va_args__<<"]: "<<green,debug_help(__va_args__)
#define dba(arr,...) cout<<magenta<<__line__<<" ["<<#arr<<"]: "<<green,debug_md=0,debug_fill(__va_args__),debug_arr(arr,0)
#else
#define dbg(...)
#define dba(arr,...)
#endif
const char df = '\n';
const bool testing = 1;
string file_name = "";

void solve() {
}

signed main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  freopen((testing ? "input.txt" : file_name + "_input.txt").c_str(), "r", stdin);
  if (!testing) freopen((file_name + "_output.txt").c_str(), "w", stdout);
  int tt = 1;
  cin >> tt;
  for (int i = 1; i <= tt; i++) {
    cout << "Case #" << i << ": ";
    solve();
  }
  return 0;
}
