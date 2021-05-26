/**
 * Multiplies two MxN and NxP matrices.
 * Time: O(M*N*P)
 */
template<typename T>
vector<vector<T>> mat_mult(vector<vector<T>>& mat1, vector<vector<T>>& mat2) {
  int res_rows = mat1.size();
  int res_cols = mat2[0].size();
  int common = mat2.size();
  vector<vector<T>> res = vector<vector<T>>(res_rows, vector<T>(res_cols));
  for (int i = 0; i < res_rows; i++) for (int j = 0; j < res_cols; j++) for (int k = 0; k < common; k++)
    res[i][j] += mat1[i][k] * mat2[k][j];
  return res;
}
/**
 * Raises an NxN matrix to the b power.
 * Time: O(log(b)*N^3)
 */
template<typename T>
vector<vector<T>> mat_pow(vector<vector<T>>& mat, long long b) {
  assert(mat.size() == mat[0].size());
  vector<vector<T>> res = vector<vector<T>>(mat.size(), vector<T>(mat[0].size()));
  for (int i = 0; i < (int) res.size(); i++) res[i][i] = 1;
  for (; b > 0; mat = mat_mult(mat, mat), b >>= 1) if (b&1) res = mat_mult(res, mat);
  return res;
}