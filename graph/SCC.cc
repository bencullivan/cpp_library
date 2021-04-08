//#define USE_SET
/*
    Finds all strongly connected components of a directed graph with N vertices and M edges.
    Time: O(N+M)
*/
struct SCC {
    vector<vector<int>> G;
    vector<vector<int>> G_rev;
#ifdef USE_SET
    vector<unordered_set<int>> G_scc;
    vector<unordered_set<int>> sccs;
#else
    vector<vector<int>> G_scc;
    vector<vector<int>> sccs;
#endif
    vector<int> order;
    vector<int> which_scc;

    SCC(int _n) : G(_n), G_rev(_n), which_scc(_n) {}

    inline void add_edge(int u, int v) {
        G[u].push_back(v);
        G_rev[v].push_back(u);
    }

    // orders the vertices in increasing order of lasts
    void order_vertices(int current_vertex) {
        if (which_scc[current_vertex] != -1) {
            return;
        }
        which_scc[current_vertex] = 0;
        for (int neighbor:G[current_vertex]) {
            order_vertices(neighbor);
        }
        order.push_back(current_vertex);
    }

    // builds a single scc
#ifdef USE_SET
    void dfs(int current_vertex, unordered_set<int>& current_scc, unordered_set<int>& neighbors) {
        current_scc.insert(current_vertex);
#else
    void dfs(int current_vertex, vector<int>& current_scc, vector<int>& neighbors) {
        current_scc.push_back(current_vertex);
#endif
        which_scc[current_vertex] = sccs.size();
        for (int neighbor:G_rev[current_vertex]) {
            if (which_scc[neighbor] == -1) {
                dfs(neighbor, current_scc, neighbors);
            } else if (which_scc[neighbor] != which_scc[current_vertex]) {
#ifdef USE_SET
                neighbors.insert(which_scc[neighbor]);
#else
                neighbors.push_back(which_scc[neighbor]);
#endif
            }
        }
    }

    // builds the DAG of sccs as well as labels each vertex with the scc it belongs to
    // builds G_scc and sccs in topological order of sccs
    void get_sccs() {
        order.clear();
        fill(which_scc.begin(), which_scc.end(), -1);
        for (int i = 0; i < (int) G.size(); i++) {
            order_vertices(i);
        }
        assert(order.size() == G.size());
        fill(which_scc.begin(), which_scc.end(), -1);
        for (int i = G.size()-1; i >= 0; i--) {
            if (which_scc[order[i]] == -1) {
#ifdef USE_SET
                unordered_set<int> current_scc;
                unordered_set<int> neighbors;
#else
                vector<int> current_scc;
                vector<int> neighbors;
#endif
                dfs(order[i], current_scc, neighbors);
                sccs.push_back(current_scc);
                G_scc.push_back(neighbors);
            }
        }
    }
}; // SCC