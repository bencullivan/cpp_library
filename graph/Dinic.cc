/*
    Max flow using Dinic's algorithm.
    O(E*V^2)
    Source: https://cp-algorithms.com/graph/dinic.html
*/
struct Dinic {
    vector<vector<int>> adj;
    vector<pair<int, int>> cut;
    vector<int> to;
    vector<long long> cap;
    vector<int> level;
    vector<int> ptr;
    queue<int> q;
    int source;
    int sink;
    long long mf = 0;
    const long long MAX_CAP = 5e18;

    Dinic(int _n) : adj(_n), level(_n), ptr(_n) {}

    inline void reserve(int _m) {
        to.reserve(_m);
        cap.reserve(_m);
    }

    void init(vector<array<long long, 3>>& edg) {
        for (array<long long, 3>& v:edg) {
            add_edge(v[0], v[1], v[2]);
        }
    }

    inline void add_edge(int u, int v, long long c) {
        to.push_back(v);
        cap.push_back(c);
        adj[u].push_back(cap.size() - 1);
        to.push_back(u);
        cap.push_back(0);
        adj[v].push_back(cap.size() - 1);
    }

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