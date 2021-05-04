template<typename T>
struct LinearSystem {
	const T eps = 1e-10;
	vector<vector<T>> A; // the augmented matrix
	vector<vector<T>> RREF;
	vector<vector<T>> inv;
	T determinant;
	int M, N;

	LinearSystem(int _M, int _N) : A(_M, vector<T>(_N)), M(_M), N(_N) {}

	void row_reduce() {
		if (RREF.empty()) {
			return;
		}
		RREF.resize(M, vector<T>(N));

	}
}; // LinearSystem

