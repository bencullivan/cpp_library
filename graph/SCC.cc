/**
* Kosaraju's Algorithm
* Finds all strongly connected components of a directed graph with N vertices and M edges.
* Time: O(N+M)
* Source: CS31 Lecture Notes - Deeparnab Chakrabarty, folklore
*/
struct SCC {
	std::vector<std::vector<int>> G; // the directed input graph
	std::vector<std::vector<int>> G_rev; // the reversed graph
	std::vector<std::vector<int>> G_scc; // the DAG of sccs
	std::vector<std::vector<int>> sccs; // the sccs
	std::vector<int> order; // for topological sort
	std::vector<int> which_scc; // which_scc[i] is the number of the scc that vertex i belongs to

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
	void dfs(int current_vertex, std::vector<int>& current_scc, std::vector<int>& neighbors) {
		current_scc.push_back(current_vertex);
		which_scc[current_vertex] = sccs.size();
		for (int neighbor:G_rev[current_vertex]) {
			if (which_scc[neighbor] == -1) {
				dfs(neighbor, current_scc, neighbors);
			}
			else if (which_scc[neighbor] != which_scc[current_vertex]) {
				neighbors.push_back(which_scc[neighbor]);
			}
		}
	}

	// builds the DAG of sccs as well as labels each vertex with the scc it belongs to
	// builds G_scc and sccs in topological order of sccs
	void get_sccs() {
		order.clear();
		std::fill(which_scc.begin(), which_scc.end(), -1);
		for (int i = 0; i < (int) G.size(); i++) {
			order_vertices(i);
		}
		assert(order.size() == G.size());
		std::fill(which_scc.begin(), which_scc.end(), -1);
		for (int i = G.size()-1; i >= 0; i--) {
			if (which_scc[order[i]] == -1) {
				std::vector<int> current_scc;
				std::vector<int> neighbors;
				dfs(order[i], current_scc, neighbors);
				sccs.push_back(current_scc);
				G_scc.push_back(neighbors);
			}
		}
	}
}; // SCC