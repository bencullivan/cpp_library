// gets matrix into REF (optionally RREF)
// returns the number of pivots
// roughly cubic complexity
template<typename T> int reduce(vector<vector<T>> &mat, bool rref=false) {
	int N = mat.size(); // num rows
	assert(N);
	int M = mat[0].size(); // num columns
	assert(M);

	int piv = 0;
	for (int col = 0; col < M; col++) {
		int found = -1;
		for (int row = piv; row < N; row++) {
			if (mat[row][col] != 0) {
				found = row;
				break;
			}
		}
		if (found == -1) continue;
		if (found != piv) {
			mat[piv].swap(mat[found]);
		}
		if (mat[piv][col] != 1) {
			T factor = T(1) / mat[piv][col];
			for (int i = col; i < M; i++) {
				mat[piv][i] *= factor;
			}
		}
		for (int row = piv+1; row < N; row++) {
			if (mat[row][col] != 0) {
				T factor = mat[row][col];
				for (int i = col; i < M; i++) {
					mat[row][i] -= mat[piv][i] * factor;
				}
			}
		}
		piv++;
	}
	if (!rref) return piv;

	for (int row = piv-1; row > 0; row--) {
		int col = 0;
		while (col < M && mat[row][col] == 0) col++;
		assert(col < M);
		for (int above = row-1; above >= 0; above--) {
			if (mat[above][col] != 0) {
				T factor = mat[above][col];
				for (int i = col; i < M; i++) {
					mat[above][i] -= mat[row][i] * factor;
				}
			}
		}
	}
	return piv;
}
