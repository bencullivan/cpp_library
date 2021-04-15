template<typename T>
using matrix = vector<vector<T>>;

template<typename T>
matrix<T> mat_mult(matrix<T>& mat1, matrix<T>& mat2) {
    int result_rows = mat1.size();
    int result_cols = mat2[0].size();
    int common = mat2.size();
    matrix<T> result = matrix<T>(result_rows, vector<T>(result_cols));
    for (int i = 0; i < result_rows; i++) {
        for (int j = 0; j < result_cols; j++) {
            for (int k = 0; k < common; k++) {
                result[i][j] += mat1[i][k] * mat2[k][j];
            }
        }
    }
    return result;
}

template<typename T>
matrix<T> mat_pow(matrix<T>& mat, long long b) {
    assert(mat.size() == mat[0].size());
    matrix<T> res = matrix<T>(mat.size(), vector<T>(mat[0].size()));
    for (int i = 0; i < (int) res.size(); i++) res[i][i] = 1;
    for (; b > 0; mat = mat_mult(mat, mat), b >>= 1) if (b&1) res = mat_mult(res, mat);
    return res;
}