/*
	2D Fenwick tree for rectangular sum queries and point updates on a 2D matrix.
	1-indexed.
	Time: 
		- build_Fenwick2d: O(N*M*log(N*M))
		- upd: O(log(N*M))
		- get: O(log(N*M))
	Sources:
		- https://cp-algorithms.com/data_structures/fenwick.html
		- https://www.topcoder.com/community/competitive-programming/tutorials/binary-indexed-trees/
		- https://www.geeksforgeeks.org/two-dimensional-binary-indexed-tree-or-fenwick-tree/
*/
template<typename T> 
struct Fenwick2d {
	vector<vector<T>> data;
	int N, M;

	Fenwick2d(int _N, int _M) : N(_N), M(_M), data(_N + 1, vector<T>(_M + 1)) {}

	Fenwick2d(vector<vector<T>>& input) : N(input.size()), M(input[0].size()),
		data(input.size() + 1, vector<T>(input[0].size() + 1)) { 
		build_Fenwick2d(input); 
	}

	void build_Fenwick2d(vector<vector<T>>& input) {
		for (int i = 1; i <= N; i++) {
			for (int j = 1; j <= M; j++) {
				upd(i, j, input[i - 1][j - 1]);
			}
		}
	}

	// adds value to the element at (x, y)
	void upd(int a, int b, T value) {
		for (int i = a; i <= N; i += i & -i) {
			for (int j = b; j <= M; j += j & -j) {
				data[i][j] += value;
			}
		}
	}

	// gets the sum of the rectangle with top left corner (1, 1) and bottom right corner (a, b)
	T get(int a, int b) {
		T sum = 0;
		for (int i = a; i > 0; i -= i & -i) {
			for (int j = b; j > 0; j -= j & -j) {
				sum += data[i][j];
			}
		}
		return sum;
	}

	// gets the sum of the rectangle with top left corner (a, b) and bottom right corner (c, d)
	T get(int a, int b, int c, int d) {
		return get(c, d) - get(c, b - 1) - get(a - 1, d) + get(a - 1, b - 1);
	}
}; // Fenwick2d 