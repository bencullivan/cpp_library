template<typename T>
std::vector<std::string> split(const std::string& s, T is_split_char) {
	int a = 0, b = 0, n = s.size();
	std::vector<std::string> r;
	while (b < n) {
		while (b < n && !is_split_char(s[b])) b++;
		r.push_back(s.substr(a, b - a));
		while (b < n && is_split_char(s[b])) b++;
		a = b;
	}
	return r;
}
std::vector<std::string> split(const std::string& s) {
	return split(s, [](char c){return c == ' ';});
}