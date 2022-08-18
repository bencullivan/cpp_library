/*
    Multiplies two MxN and NxP matrices, stores the MxP result in store.
    Time: O(M*N*P)
*/
template <typename T>
void mat_mult(std::vector<std::vector<T>> &mat1,
              std::vector<std::vector<T>> &mat2,
              std::vector<std::vector<T>> &store) {
    int res_rows = mat1.size();
    int res_cols = mat2[0].size();
    int common = mat2.size();
    for (int i = 0; i < res_rows; i++)
        std::fill(store[i].begin(), store[i].end(), 0); // ensure 0 is default
    for (int i = 0; i < res_rows; i++) {
        for (int k = 0; k < common; k++) {
            T r = mat1[i][k];
            for (int j = 0; j < res_cols; j++) {
                store[i][j] += r * mat2[k][j];
            }
        }
    }
    // for (int i = 0; i < res_rows; i++) for (int j = 0; j < res_cols; j++) for
    // (int k = 0; k < common; k++)
    //     store[i][j] += mat1[i][k] * mat2[k][j];
}
/*
    Raises an NxN matrix to the b power.
    Time: O(log(b)*N^3)
*/
template <typename T>
std::vector<std::vector<T>> mat_pow(std::vector<std::vector<T>> mat,
                                    long long b) {
    assert(mat.size() > 0 && mat.size() == mat[0].size());
    std::vector<std::vector<T>> res =
        std::vector<std::vector<T>>(mat.size(), std::vector<T>(mat.size()));
    std::vector<std::vector<T>> store =
        std::vector<std::vector<T>>(mat.size(), std::vector<T>(mat.size()));
    for (int i = 0; i < (int)res.size(); i++)
        res[i][i] = 1;
    while (b > 0) {
        if (b & 1) {
            mat_mult(res, mat, store);
            res.swap(store);
        }
        mat_mult(mat, mat, store);
        mat.swap(store);
        b >>= 1;
    }
    return res;
}
// ones on diagonal above main diagonal, coefficients of recurrence in last row