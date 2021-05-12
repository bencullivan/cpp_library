typedef __int128 LL;
LL stoi128(const string& s) {
	LL a = 0;
	int start = s[0] == '-';
	for (int i = start; i < (int)s.size(); i++) a = a * 10 + s[i] - '0';
	if (start) return -a;
	return a;
}
void print128(ostream& os, LL a) {
	if (a < 0) os << '-', a = -a;
	if (a > 9) print128(os, a / 10);
	os << int(a % 10);
}
istream& operator >> (istream& is, LL& a) {
	// string s; is >> s; a = stoi128(s); return is; // if the input doesn't fit in a long long
	ll v; is >> v; a = v; return is; // if the input fits in a long long
}
ostream& operator << (ostream& os, const LL& a) {
	print128(os, a);
	return os;
}