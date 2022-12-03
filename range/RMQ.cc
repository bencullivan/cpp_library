// Build in O(N*log(N)). Query in O(1). Sources: kactl, Neal Wu.
template <typename T, typename CompT = std::less<T>> struct RMQ {
  CompT comp;
  std::vector<T> vals;
  std::vector<std::vector<int>> table;
  int select_index(int a, int b) { return comp(vals[a], vals[b]) ? a : b; }
  RMQ() {}
  RMQ(const std::vector<T> &_vals) { build(_vals); }
  void build(const std::vector<T> &_vals) {
    vals = _vals;
    table.resize(1, std::vector<int>(vals.size()));
    for (int i = 0; i < (int)vals.size(); i++)
      table[0][i] = i;
    for (int pw = 1, k = 1; pw * 2 <= (int)vals.size(); pw *= 2, k++) {
      table.emplace_back((int)vals.size() - pw * 2 + 1);
      for (int j = 0; j < (int)table[k].size(); j++)
        table[k][j] = select_index(table[k - 1][j], table[k - 1][j + pw]);
    }
  }
  int get_index(int a, int b) { // gets the minimum of the range [a, b)
    int dep = 31 - __builtin_clz(b - a);
    return select_index(table[dep][a], table[dep][b - (1 << dep)]);
  }
  T get_val(int a, int b) { return vals[get_index(a, b)]; }
}; // RMQ