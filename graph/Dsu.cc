/*
    Disjoint set union.
*/
struct Dsu {
    vector<int> par;
    vector<int> sz;

    Dsu(int _n) : par(_n, -1), sz(_n, 1) {}

    int find(int x) {
        return par[x] < 0 ? x : par[x] = find(par[x]);
    }

    bool same(int x, int y) {
        return find(x) == find(y);
    }

    bool unite(int x, int y) {
        x = find(x);
        y = find(y);
        if (x == y) return false;
        if (sz[x] < sz[y]) swap(x, y);
        sz[x] += sz[y];
        par[y] = x;
        return true;
    }

    int size(int x) {
        return sz[find(x)];
    }
}; // Dsu