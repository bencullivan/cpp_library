/**
 * Disjoint Set Union
 * Time: O(alpha(N)) (amortized) alpha(N) will not exceed 4
 */
struct DSU {
	vector<int> par; // par[i] is the parent vertex of vertex i or -size if i is a head

	DSU(int _n) : par(_n, -1) {}

	// returns the head of x's set (performs path compression)
	int find(int x) {
		if (par[x] < 0) {
			return x;
		} else {
			return par[x] = find(par[x]);
		}
	}

	// unites the sets with heads x and y
	// returns whether x and y were in different sets
	bool unite(int x, int y) {
		x = find(x);
		y = find(y);
		if (x == y) {
			return false;
		}
		if (par[x] > par[y]) {
			swap(x, y);
		}
		par[x] += par[y];
		par[y] = x;
		return true;
	}

	// returns the size of x's set
	int size(int x) {
		return -par[find(x)];
	}
}; // DSU