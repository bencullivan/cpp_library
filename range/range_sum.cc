// get sum over the range [l, r]
template <typename T> T range_sum(const vector<T> &v, int l, int r) {
	r = min(r, (int)v.size() - 1);
	l = max(l, 0);
	if (r < l) return 0;
	T ans = v[r];
	if (l) ans -= v[l - 1];
	return ans;
}