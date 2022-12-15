template <typename T, class Fun>
void generate_vectors(size_t i, std::vector<T> &options, std::vector<T> &v, Fun &f) {
	if (i >= v.size()) {
		f(v);
		return;
	}
	for (T x : options) {
		v[i] = x;
		generate_vectors(i + 1, options, v, f);
	}
}
 
template <typename T, class Fun>
void generate_vectors(std::vector<T> options, size_t len, Fun &f) {
	std::vector<T> v(len);
	generate_vectors(0, options, v, f);
}
 
template <class Fun>
void generate_vectors(int min_num, int max_num, size_t len, Fun &f) {
	std::vector<int> v(len);
	std::vector<int> options(max_num - min_num + 1);
	std::iota(options.begin(), options.end(), min_num);
	generate_vectors(0, options, v, f);
}