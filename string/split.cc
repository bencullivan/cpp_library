vector<string> split(const string& s, const char split_char) {
    int a = 0, b = 0, n = s.size();
    vector<string> r;
    while (b < n) {
        while (b < n && s[b] != split_char) b++;
        r.push_back(s.substr(a, b - a));
        while (b < n && s[b] == split_char) b++;
        a = b;
    }
    return r;
}