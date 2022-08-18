#include <bits/stdc++.h>
#ifndef NOT_ONLINE_JUDGE
#define dbg(...) 0
#define dba(...) 0
#endif
using namespace std;
using ll = long long;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
using vi = vector<int>;
using vvi = vector<vector<int>>;
using vl = vector<ll>;
using vvl = vector<vector<ll>>;
using vb = vector<bool>;
using vvb = vector<vector<bool>>;
using vpi = vector<pii>;
using vpl = vector<pll>;
using vs = vector<string>;
template <typename T> using minpq = priority_queue<T, vector<T>, greater<T>>;
template <typename T, typename U> bool ckmin(T &t, const U &u) {
    return u < t ? t = u, true : false;
}
template <typename T, typename U> bool ckmax(T &t, const U &u) {
    return u > t ? t = u, true : false;
}
#define each(i, a) for (auto &i : a)
#define rep(i, n) for (int i = 0; i < (n); i++)
#define rep1(i, n) for (int i = 1; i <= (n); i++)
#define sz(v) int(v.size())
#define mp make_pair
#define pb push_back
#define mb emplace_back
#define lb lower_bound
#define ub upper_bound
#define fi first
#define se second
#define all(v) v.begin(), v.end()
// end of template

void solve(int _) {
}
signed main() {
    ios_base::sync_with_stdio(0), cin.tie(0);
    int T;
    cin >> T;
    rep1(i, T) {
        cout << "Case #" << i << ": ";
        solve(i);
    }
}