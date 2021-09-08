#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ull = unsigned long long;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
template<typename T> using minpq = priority_queue<T, vector<T>, greater<T>>;
#ifdef BCDBG  // debugging 
#define GREEN   "\033[32m"
#define MAGENTA "\033[35m"
#define RESET   "\033[0m"
template<typename T, typename U> ostream& operator << (ostream& os, const pair<T, U>& p) {return os << "(" << p.first << ", " << p.second << ")";}
template<typename T, typename U = typename enable_if<!is_same<T, string>::value, typename T::value_type>::type> ostream& operator << (ostream& os, const T& v) {os << "\n{"; string sep = ""; for (const U& x:v) os << sep << x, sep = ", "; return os << "}";}
void _dbg() {cerr << RESET << endl;}
template<typename T, typename... U> void _dbg(T t, U... u) {cerr << t << (sizeof...(u) ? ", " : ""), _dbg(u...);}
int _dm[10], _mx;
void _dbf() {}
template<typename T, typename... U> void _dbf(T t, U... u) {_dm[_mx++] = t, _dbf(u...);}
template<typename T> void _dba(T x, int d) {cerr << x;}
template<typename T> void _dba(T* a, int d) {cerr << "\n{"; string sep = ""; for (int i = 0; i < _dm[d]; i++) cerr << sep, sep = ", ", _dba(a[i], d + 1); cerr << "}" << (d == 0 ? RESET : "") << endl;}
#define dbg(...) cerr << MAGENTA << __LINE__ << " [" << #__VA_ARGS__ << "]: " << GREEN, _dbg(__VA_ARGS__)
#define dba(a,...) cerr << MAGENTA << __LINE__ << " [" << #a << "]: " << GREEN, _mx = 0, _dbf(__VA_ARGS__), _dba(a, 0)
#else
#define dbg(...) 1
#define dba(a,...) 1
#endif  // debugging
#define cinv(v) for (auto& _x:v) cin >> _x
#define cina(v,s,e) for (int _i=(s);_i<(e);_i++) cin >> v[_i]
#define all(v) v.begin(),v.end()
#define rall(v) v.rbegin(),v.rend()
#define sz(v) (int)v.size()
#define vec vector
#define mp make_pair
#define fi first
#define se second
#define pb push_back
#define eb emplace_back
#define lb lower_bound
#define ub upper_bound
#define df '\n'

void solve() {
    
}

signed main() {
    ios_base::sync_with_stdio(0), cin.tie(0);
    int tt = 1;
    cin >> tt;
    while (tt--) solve();
    return 0;
}