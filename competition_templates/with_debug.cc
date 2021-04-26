#include <bits/stdc++.h>

#ifdef LOCAL
#ifndef LOL_DEBUG
#define LOL_DEBUG
#define dba1(_arr,_d1) { \
    std::cerr << __LINE__ << " [" << #_arr << "]:" << "\n{"; \
    for (long long _i = 0; _i < _d1; _i++) { \
        std::cerr << _arr[_i]; \
        if (_i < _d1-1) std::cerr << ", "; \
    } \
    std::cerr << "}" << endl; }
#define dba2(_arr,_d1,_d2) { \
    std::cerr << __LINE__ << " [" << #_arr << "]:" << "\n{"; \
    for (long long _i = 0; _i < _d1; _i++) { \
        std::cerr << "\n{"; \
        for (long long _j = 0; _j < _d2; _j++) { \
            std::cerr << _arr[_i][_j]; \
            if (_j < _d2-1) std::cerr << ", "; \
        } \
        std::cerr << "},"; \
    } \
    std::cerr << "}" << std::endl; }
template<typename K, typename V> 
std::ostream& operator<<(std::ostream& os, const std::pair<K, V>& p) {
    return os << "(" << p.first << ", " << p.second << ")";
}
template<typename T_container, typename T = typename std::enable_if<!std::is_same<T_container, std::string>::value, typename T_container::value_type>::type> 
std::ostream& operator<<(std::ostream &os, const T_container &v) {
    os << "\n{";
    std::string sep;
    for (const T &x : v) os << sep << x, sep = ", ";
    return os << "}";
}
void debug_helper() {
    std::cerr << std::endl;
}
template<typename Head, typename... Tail> 
void debug_helper(Head H, Tail... T) {
    std::cerr << H;
    if (sizeof...(T)) {
        std::cerr << ", "; 
    }
    debug_helper(T...);
}
#define dbg(...) std::cerr << __LINE__ << " [" << #__VA_ARGS__ << "]: ", debug_helper(__VA_ARGS__)
#endif // LOL_DEBUG
#else
#define dba1(_arr,_d1)
#define dba2(_arr,_d1,_d2)
#define dbg(...)
#endif // LOCAL

typedef long long ll;
using namespace std;

void solve() {
}

signed main() {
    ios_base::sync_with_stdio(0), cin.tie(0);
    int tt = 1;
    //cin >> tt;
    for (int i = 1; i <= tt; i++) {
        solve();
    }
    return 0;
}