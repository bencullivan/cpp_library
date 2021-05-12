typedef __int128_t LL;
typedef __uint128_t ULL;

template<typename T128>
void print(const T128& a, bool first = true) {
	if (first) {
		if (a < 0) cout << '-';
		else if (a == 0) {
			cout << '0';
			return;
		}
	}
	if (a == 0) return;
	print(a / 10, false);
	cout << int(a % 10);
}