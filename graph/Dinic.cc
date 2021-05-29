/**
* Max flow using Dinic's algorithm.
* Time: O(E*V^2)
* Source: https://cp-algorithms.com/graph/dinic.html
*/
struct Dinic {
  vector<vector<int>> adj; // adj[i] is the list of indices of the out-edges of the ith vertex
  vector<pair<int, int>> cut; // the edges that form the min s-t cut
  vector<int> to; // to[i] is the vertex that the ith edge points to
  vector<long long> cap; // cap[i] is the capacity of the ith edge
  vector<int> level; // level[i] is the level of the ith vertex
  vector<int> ptr; // ptr[i] points to the next unvisited neighbor of the ith vertex
  queue<int> q;
  int source;
  int sink;
  long long mf = 0; // the value of the max s-t flow
  const long long MAX_CAP = 5e18; // the maximum edge capacity

  // constructs a redisual network with no edges
  Dinic(int _n) : adj(_n), level(_n), ptr(_n) {}

  // allocates space for _m/2 edges
  inline void reserve(int _m) {
    to.reserve(_m);
    cap.reserve(_m);
  }

  // initializes the residual network with the provided list of edges
  void init(vector<array<long long, 3>>& edg) {
    for (array<long long, 3>& v:edg) {
      add_edge(v[0], v[1], v[2]);
    }
  }

  // adds the edge with the given capacity and the reverse edge to the residual network
  inline void add_edge(int u, int v, long long c) {
    to.push_back(v);
    cap.push_back(c);
    adj[u].push_back(cap.size() - 1);
    to.push_back(u);
    cap.push_back(0);
    adj[v].push_back(cap.size() - 1);
  }

  // finds the level of each reachable vertex, beginning from the source
  // returns whether the sink is reachable from the source
  bool bfs() {
    fill(level.begin(), level.end(), -1);
    level[source] = 0;
    q.push(source);
    while (!q.empty()) {
      int u = q.front();
      q.pop();
      for (int x:adj[u]) {
        if (level[to[x]] == -1 && cap[x] > 0) {
          q.push(to[x]);
          level[to[x]] = level[u] + 1;
        }
      }
    }
    return level[sink] != -1;
  }

  // attempts to push 'push_flow' units of flow from vertex u toward the sink i.e. up a level
  // returns the number of units that were pushed
  long long dfs(int u, long long push_flow) {
    if (u == sink || push_flow == 0) {
      return push_flow;
    }
    for (; ptr[u] < (int) adj[u].size(); ptr[u]++) {
      int x = adj[u][ptr[u]];
      if (level[u] + 1 == level[to[x]] && cap[x] > 0) {
        long long pushed = dfs(to[x], min(push_flow, cap[x]));
        if (pushed > 0) {
          cap[x] -= pushed;
          cap[x ^ 1] += pushed;
          return pushed;
        }
      }
    }
    return 0;
  }

  // finds the max s-t flow
  long long max_flow(int s, int t) {
    source = s;
    sink = t;
    mf = 0;
    while (bfs()) {
      fill(ptr.begin(), ptr.end(), 0);
      while (1) {
        long long pushed = dfs(source, MAX_CAP);
        if (pushed == 0) {
          break;
        }
        mf += pushed;
      }
    }
    return mf;
  }

  // finds the min s-t cut
  void min_cut() {
    bfs();
    for (int u = 0; u < (int) level.size(); u++) {
      if (level[u] != -1) {
        for (int x:adj[u]) {
          if ((x & 1) == 0 && level[to[x]] == -1 && cap[x] <= 0) {
            cut.emplace_back(u, to[x]);
          }
        }
      }
    }
  }
}; // Dinic