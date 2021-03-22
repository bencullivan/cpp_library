/*
    Disjoint set union.
*/
struct Dsu {
    std::vector<int> par; // par[i] is the parent vertex of vertex i or -1 if i is a head
    std::vector<int> sz; // sz[i] is the size of the set with head i

    Dsu(int _n) : par(_n, -1), sz(_n, 1) {}

    // returns the head of x's set (performs path compression)
    int find(int x) {
        return par[x] < 0 ? x : par[x] = find(par[x]);
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
}; // Dsu