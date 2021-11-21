template<typename T> vector<string> split(const string& s, T is_split_char) {
	int a = 0, b = 0, n = s.size();
	vector<string> r;
	while (b < n) {
		while (b < n && !is_split_char(s[b])) b++;
		r.push_back(s.substr(a, b - a));
		while (b < n && is_split_char(s[b])) b++;
		a = b;
	}
	return r;
}
vector<string> split(const string& s) {
	return split(s, [](char c){return c == ' ';});
}