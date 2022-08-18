// 2D Fenwick tree for rectangular sum queries and point updates on a 2D matrix
// in O(log(N*M)) 1-indexed. Sources:
//     - https://cp-algorithms.com/data_structures/fenwick.html
//     -
//     https://www.topcoder.com/community/competitive-programming/tutorials/binary-indexed-trees/
//     -
//     https://www.geeksforgeeks.org/two-dimensional-binary-indexed-tree-or-fenwick-tree/
template <typename T> struct Fenwick2d {
    int N, M;
    std::vector<std::vector<T>> data;
    Fenwick2d(int _N, int _M)
        : N(_N), M(_M), data(_N + 1, std::vector<T>(_M + 1)) {}
    // adds value to the element at (x, y)
    void upd(int a, int b, T value) {
        for (int i = a; i <= N; i += i & -i)
            for (int j = b; j <= M; j += j & -j)
                data[i][j] += value;
    }
    // gets the sum of the rectangle with top left corner (1, 1) and bottom
    // right corner (a, b)
    T get(int a, int b) {
        T sum = 0;
        for (int i = a; i > 0; i -= i & -i)
            for (int j = b; j > 0; j -= j & -j)
                sum += data[i][j];
        return sum;
    }
    // gets the sum of the rectangle with top left corner (a, b) and bottom
    // right corner (c, d)
    T get(int a, int b, int c, int d) {
        return get(c, d) - get(c, b - 1) - get(a - 1, d) + get(a - 1, b - 1);
    }
}; // struct Fenwick2d
