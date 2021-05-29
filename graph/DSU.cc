// Disjoint Set Union
// Time: (amortized) O(alpha(N)) (alpha(N) will not exceed 4)
struct DSU {
  vector<int> par; // par[i] is the parent vertex of vertex i or -size if i is a head
  DSU(int _n) : par(_n, -1) {}
  int find(int x) { return par[x] < 0 ? x : par[x] = find(par[x]); } // returns the head of x's set
  int size(int x) { return -par[find(x)]; } // returns the size of x's set 
  bool unite(int x, int y) { // unites the sets with heads x and y, returns whether x and y were in different sets
    x = find(x), y = find(y);
    if (x == y) return false;
    if (par[x] > par[y]) swap(x, y);
    par[x] += par[y];
    par[y] = x;
    return true;
  }
}; // DSU