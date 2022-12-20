int centroid_root = 0; // the root of the centroid tree

int get_sizes(int u, int v, const std::vector<std::vector<int>> &tr,
							std::vector<int> &sizes, std::vector<bool> &seen) {
	sizes[u] = 1;
	for (int x : tr[u])
		if (x != v && !seen[x])
			sizes[u] += get_sizes(x, u, tr, sizes, seen);
	return sizes[u];
}

int get_centroid(int u, int v, int n, const std::vector<std::vector<int>> &tr,
								std::vector<int> &sizes, std::vector<bool> &seen) {
	for (int x : tr[u])
		if (x != v && !seen[x] && sizes[x] > n / 2)
			return get_centroid(x, u, n, tr, sizes, seen);
	return u;
}

int centroid_decomp(int u, int v, std::vector<int> &par,
										const std::vector<std::vector<int>> &tr,
										std::vector<int> &sizes, std::vector<bool> &seen) {
	int n = get_sizes(u, -1, tr, sizes, seen);
	int centroid = get_centroid(u, -1, n, tr, sizes, seen);
	par[centroid] = v;
	seen[centroid] = true;
	for (int x : tr[centroid])
		if (!seen[x])
			centroid_decomp(x, centroid, par, tr, sizes, seen);
	return centroid;
}

// returns par where par[u] is the parent of u in the centroid tree
// depth of the centroid tree is guaranteed to be O(log(n))
// Time: O(n*log(n))
std::vector<int> centroid_decomp(const std::vector<std::vector<int>> &tr) {
	int n = tr.size();
	std::vector<int> par(n, -1), sizes(n);
	std::vector<bool> seen(n, false);
	centroid_root = centroid_decomp(0, -1, par, tr, sizes, seen);
	return par;
}