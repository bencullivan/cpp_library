// Build in O(N*log(N)). Query in O(1). Sources: kactl, Neal Wu.
template<typename T, bool use_min = true>
struct RMQ {
  vector<T> vals;
  vector<vector<int>> table;
  int select_index(int a, int b) {
    return (use_min ? vals[a] < vals[b] : vals[a] > vals[b]) ? a : b;
  }
  RMQ() {}
  RMQ(const vector<T>& _vals) { build(_vals); }
  void build(const vector<T>& _vals) {
    vals = _vals;
    table.resize(1, vector<int>(vals.size()));
    for (int i = 0; i < (int)vals.size(); i++) table[0][i] = i;
    for (int pw = 1, k = 1; pw * 2 <= (int)vals.size(); pw *= 2, k++) {
      table.emplace_back((int)vals.size() - pw * 2 + 1);
      for (int j = 0; j < (int)table[k].size(); j++) 
        table[k][j] = select_index(table[k - 1][j], table[k - 1][j + pw]);
    }
  }
  T get_index(int a, int b) { // gets the minimum of the range [a, b)
    int dep = 31 - __builtin_clz(b - a);
    return select_index(table[dep][a], table[dep][b - (1 << dep)]);
  }
  T get_val(int a, int b) { return vals[get_index(a, b)]; }
}; // RMQ

// Build in O(N*log(N)). Query in O(1).
struct LCA {
  vector<int> first_euler, euler;
  vector<int> depth;
  RMQ<int> rmq;
  int id;
  LCA() {}
  LCA(int root, const vector<vector<int>>& tr) : first_euler(tr.size()) {
    euler.resize(2 * tr.size()), depth.resize(2 * tr.size());
    id = 0;
    dfs(root, -1, 0, tr);
    rmq.build(depth);
    depth.clear();
  }
  void dfs(int u, int v, int d, const vector<vector<int>>& tr) {
    first_euler[u] = id;
    euler[id] = u;
    depth[id] = d;
    id++;
    for (int x:tr[u]) if (x != v) {
      dfs(x, u, d + 1, tr);
      euler[id] = u;
      depth[id] = d;
      id++;
    }
  }
  int get_lca(int u, int v) { 
    return euler[rmq.get_index(min(first_euler[u], first_euler[v]), 
        max(first_euler[u], first_euler[v]) + 1)]; 
  }
}; // LCA
