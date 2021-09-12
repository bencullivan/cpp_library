template<typename T> using matrix = vector<vector<T>>;

/**
* Fills an MxN matrix with value x
* Time: O(M*N)
*/
template<typename T>
matrix<T> mat_fill(matrix<T>& mat, T x) {
    for (size_t i = 0; i < mat.size(); i++) {
        for (size_t j = 0; j < mat.size(); j++) {
            mat[i][j] = x;
        }
    }
}

/**
* Multiplies two MxN and NxP matrices.
* Time: O(M*N*P)
*/
template<typename T>
matrix<T> mat_mult(matrix<T>& mat1, matrix<T>& mat2) {
    int res_rows = mat1.size();
    int res_cols = mat2[0].size();
    int common = mat2.size();
    matrix<T> res = matrix<T>(res_rows, vector<T>(res_cols));
    for (int i = 0; i < res_rows; i++) {
        for (int j = 0; j < res_cols; j++) {
            for (int k = 0; k < common; k++) {
                res[i][j] += mat1[i][k] * mat2[k][j];
            }
        }
    }
    return res;
}

/**
* Multiplies two MxN and NxP matrices.
* Time: O(M*N*P)
*/
template<typename T>
void mat_mult_store(matrix<T>& mat1, matrix<T>& mat2, matrix<T>& res) {
    int res_rows = mat1.size();
    int res_cols = mat2[0].size();
    int common = mat2.size();
    for (int i = 0; i < res_rows; i++) {
        for (int j = 0; j < res_cols; j++) {
            for (int k = 0; k < common; k++) {
                res[i][j] += mat1[i][k] * mat2[k][j];
            }
        }
    }
    return res;
}

/**
* Raises an NxN matrix to the b power.
* Time: O(log(b)*N^3)
*/
template<typename T>
matrix<T> mat_pow(matrix<T> mat, unsigned long long b) {
    assert(mat.size() == mat[0].size());
    T default_value = 0; // ENSURE 0 IS THE DEFAULT VALUE
    matrix<T> res(mati.size(), vector<T>(mat.size()));
    matrix<T> mat_temp(mat.size(), vector<T>(mat.size()));
    matrix<T> res_temp(mat.size(), vector<T>(mat.size()));
    for (int i = 0; i < (int) res.size(); i++) res[i][i] = 1;
    while (b > 0) {
        if (b & 1) {
            mat_fill(res_temp, default_value);
            mat_mult_store(res, mat, res_temp);
            res.swap(res_temp);
        }
        mat_fill(mat_temp, default_value);
        mat_mult_store(mat, mat, mat_temp);
        mat.swap(mat_temp);
        b >>= 1;
    }
    return res;
}

// /**
// * Multiplies two MxN and NxP matrices.
// * Time: O(M*N*P)
// */
// template<typename T>
// vector<vector<T>> mat_mult(vector<vector<T>>& mat1, vector<vector<T>>& mat2) {
//     int res_rows = mat1.size();
//     int res_cols = mat2[0].size();
//     int common = mat2.size();
//     vector<vector<T>> res = vector<vector<T>>(res_rows, vector<T>(res_cols));
//     for (int i = 0; i < res_rows; i++) for (int j = 0; j < res_cols; j++) for (int k = 0; k < common; k++)
//         res[i][j] += mat1[i][k] * mat2[k][j];
//     return res;
// }
// /**
// * Raises an NxN matrix to the b power.
// * Time: O(log(b)*N^3)
// */
// template<typename T>
// vector<vector<T>> mat_pow(vector<vector<T>>& mat, long long b) {
//     assert(mat.size() == mat[0].size());
//     vector<vector<T>> res = vector<vector<T>>(mat.size(), vector<T>(mat[0].size()));
//     for (int i = 0; i < (int) res.size(); i++) res[i][i] = 1;
//     for (; b > 0; mat = mat_mult(mat, mat), b >>= 1) if (b&1) res = mat_mult(res, mat);
//     return res;
// }