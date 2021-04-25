/*
    Disjoint Set Union.
    Time:
        all operations: O(\alpha(N)) (amortized)
                        \alpha(N) will not exceed 4
*/
struct DSU {
    vector<int> par; // par[i] is the parent vertex of vertex i or -1 if i is a head
    vector<int> sz; // sz[i] is the size of the set with head i

    DSU(int _n) : par(_n, -1), sz(_n, 1) {}

    // returns the head of x's set (performs path compression)
    int find(int x) {
        if (par[x] < 0) {
            return x;
        } else {
            return par[x] = find(par[x]);
        }
    }

    // returns whether x and y are in the same set
    bool same(int x, int y) {
        return find(x) == find(y);
    }

    // unites the sets with heads x and y
    // returns whether x and y were in different sets
    bool unite(int x, int y) {
        x = find(x);
        y = find(y);
        if (x == y) return false;
        if (sz[x] < sz[y]) swap(x, y);
        sz[x] += sz[y];
        par[y] = x;
        return true;
    }

    // returns the size of x's set
    int size(int x) {
        return sz[find(x)];
    }
}; // DSU