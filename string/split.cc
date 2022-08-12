std::vector<std::string> split(const std::string& s, char split_char = ' ') {
    int a = 0, b = 0, n = s.size();
    std::vector<std::string> r;
    while (b < n) {
        while (b < n && s[b] != split_char) b++;
        r.push_back(s.substr(a, b - a));
        while (b < n && s[b] == split_char) b++;
        a = b;
    }
    return r;
}