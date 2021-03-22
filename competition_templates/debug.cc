// This is the code that is included on line 5 of the templates
// source: neal (cf)

template<typename K, typename V> ostream& operator<<(ostream& os, const pair<K, V>& p) {
    return os << "(" << p.first << ", " << p.second << ")";
}

template<typename T_container, typename T = typename enable_if<!is_same<T_container, string>::value, typename T_container::value_type>::type> ostream& operator<<(ostream &os, const T_container &v) {
    os << "\n{";
    string sep;
    for (const T &x : v) os << sep << x, sep = ", ";
    return os << '}';
}

void debug_helper() {
    cerr << endl;
}

template<typename Head, typename... Tail> void debug_helper(Head H, Tail... T) {
    cerr << H; if (sizeof...(T)) cerr << ", "; debug_helper(T...);
}

/*
template<typename T> void debug_container(string name, T begin, T end, int line_num) {
    cerr << line_num << ": " << name << " = {";
    while (begin != end) {
        cerr << (*begin);
        ++begin;
        if (begin != end) cerr << ", ";
    }
    cerr << "}" << endl;
}
*/

#define dbg(...) cout << __LINE__ << " [" << #__VA_ARGS__ << "]: ", debug_helper(__VA_ARGS__)
//#define dbc(container) debug_container(#container, (container).begin(), (container).end(), __LINE__)
//#define dbci(star,ende) debug_container(#star, star, ende, __LINE__)