// finds an eulerian path in an undirected graph in O(n)
// instead of vertices, the adjacency list `graph` contains the indices of edges each vertex is adjaent to
// each adjacency list is rotated one index to the left
std::vector<int> eulerian_path_undirected_graph(std::vector<std::vector<int>>& graph, std::vector<std::vector<int>>& edges) {
    int n = graph.size();
    int m = edges.size();
    std::vector<int> last(n);
    int odd = 0;
    int a = -1, b = -1;
    for (int i = 0; i < n; i++) {
        int s = graph[i].size();
        last[i] = s-1;
        if (s&1) {
            odd++;
            if (a == -1) a = i;
            else b = i;
        }
    }
    if (odd == 0) a = b = 0;
    else if (odd == 2) {
        graph[a].push_back(m);
        graph[b].push_back(m);
        edges.push_back({a, b});
    } else return {};
    std::vector<bool> used(m, false);
    std::vector<int> st, res;
    res.reserve(m+1);
    st.reserve(n);
    st.push_back(a);
    while (!st.empty()) {
        int cur = st.back();
        while (last[cur] >= 0 && used[graph[cur][0]]) std::swap(graph[cur][0], graph[cur][last[cur]--]);
        if (last[cur] < 0) {
            res.push_back(cur);
            st.pop_back();
        } else {
            st.push_back(edges[graph[cur][0]][0] == cur ? edges[graph[cur][0]][1] : edges[graph[cur][0]][0]);
            used[graph[cur][0]] = true;
            std::swap(graph[cur][0], graph[cur][last[cur]--]);
        }
    }
    return res;
}
// finds an eulerian path in a directed graph in O(n)
// each adjacency list is rotated one index to the left
std::vector<int> eulerian_path_directed_graph(std::vector<std::vector<int>>& graph) {
    int n = graph.size();
    std::vector<int> last(n), indeg(n);
    for (int i = 0; i < n; i++) for (int x:graph[i]) indeg[x]++;
    int a = -1, b = -1;
    int m = 0;
    for (int i = 0; i < n; i++) {
        int s = graph[i].size();
        m += s;
        last[i] = s-1;
        if (s != indeg[i]) {
            if (s == indeg[i]+1) {
                if (a != -1) return {};
                a = i;
            } else if (s == indeg[i]-1) {
                if (b != -1) return {};
                b = i;
            } else return {};
        }
    }
    if (a == -1 && b == -1) a = b = 0;
    else if (a != -1 && b != -1) graph[b].push_back(a);
    else return {};
    std::vector<int> st, res;
    res.reserve(m+1);
    st.reserve(n);
    st.push_back(a);
    while (!st.empty()) {
        int cur = st.back();
        if (last[cur] < 0) {
            res.push_back(cur);
            st.pop_back();
        } else {
            st.push_back(graph[cur][0]);
            std::swap(graph[cur][0], graph[cur][last[cur]--]);
        }
    }
    std::reverse(res.begin(), res.end());
    return res;
}