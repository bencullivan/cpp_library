// mo's algorithm
// source: Competitive Programmer’s Handbook
int block_size;
struct mo {
	int l, r;
	bool operator<(const mo& other) {
		if (l/block_size == other.l/block_size) return r < other.r;
		return l/block_size < other.l/block_size;
	}
};
template<typename T, typename Add_Fn, typename Rem_Fn, typename Process_Fn>
void mo_algo(std::vector<T>& data, std::vector<mo>& queries, Add_Fn add, Rem_Fn rem, Process_Fn process_range) {
	int n = data.size();
	assert(n > 0);
	block_size = max(1, (int)sqrt(n)); // change if needed
	std::sort(queries.begin(), queries.end());
	add(data[0]);
	int l = 0, r = 0;
	for (const mo& q:queries) {
		while (l > q.l) add(data[--l]);
		while (r < q.r) add(data[++r]);
		while (l < q.l) rem(data[l++]);
		while (r > q.r) rem(data[r--]);
		process_range(q);
	}
}