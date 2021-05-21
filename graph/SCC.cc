/**
 * Kosaraju's Algorithm
 * Finds all strongly connected components of a directed graph with N vertices and M edges.
 * Time: O(N+M)
 * Source: CS31 Lecture Notes - Deeparnab Chakrabarty, folklore
 */
struct SCC {
	vector<vector<int>> G; // the directed input graph
	vector<vector<int>> G_rev; // the reversed graph
	vector<vector<int>> G_scc; // the DAG of sccs
	vector<vector<int>> sccs; // the sccs
	vector<int> order; // for topological sort
	vector<int> which_scc; // which_scc[i] is the number of the scc that vertex i belongs to

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
	void dfs(int current_vertex, vector<int>& current_scc, vector<int>& neighbors) {
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
		fill(which_scc.begin(), which_scc.end(), -1);
		for (int i = 0; i < (int) G.size(); i++) {
			order_vertices(i);
		}
		assert(order.size() == G.size());
		fill(which_scc.begin(), which_scc.end(), -1);
		for (int i = G.size()-1; i >= 0; i--) {
			if (which_scc[order[i]] == -1) {
				vector<int> current_scc;
				vector<int> neighbors;
				dfs(order[i], current_scc, neighbors);
				sccs.push_back(current_scc);
				G_scc.push_back(neighbors);
			}
		}
	}
}; // SCC

#ifndef ATCODER_INTERNAL_CSR_HPP
#define ATCODER_INTERNAL_CSR_HPP 1

namespace atcoder {

template <class E> struct csr {
	std::vector<int> start;
	std::vector<E> elist;
	explicit csr(int n, const std::vector<std::pair<int, E>>& edges)
		: start(n + 1), elist(edges.size()) {
		for (auto e : edges) {
			start[e.first + 1]++;
		}
		for (int i = 1; i <= n; i++) {
			start[i] += start[i - 1];
		}
		auto counter = start;
		for (auto e : edges) {
			elist[counter[e.first]++] = e.second;
		}
	}
};

}  // namespace atcoder

#endif  // ATCODER_INTERNAL_CSR_HPP

#ifndef ATCODER_INTERNAL_SCC_HPP
#define ATCODER_INTERNAL_SCC_HPP 1

namespace atcoder {

// Reference:
// R. Tarjan,
// Depth-First Search and Linear Graph Algorithms
struct scc_graph {
public:
	explicit scc_graph(int n) : _n(n) {}

	int num_vertices() { return _n; }

	void add_edge(int from, int to) { edges.push_back({from, {to}}); }

	// @return pair of (# of scc, scc id)
	std::pair<int, std::vector<int>> scc_ids() {
		auto g = csr<edge>(_n, edges);
		int now_ord = 0, group_num = 0;
		std::vector<int> visited, low(_n), ord(_n, -1), ids(_n);
		visited.reserve(_n);
		auto dfs = [&](auto self, int v) -> void {
			low[v] = ord[v] = now_ord++;
			visited.push_back(v);
			for (int i = g.start[v]; i < g.start[v + 1]; i++) {
				auto to = g.elist[i].to;
				if (ord[to] == -1) {
					self(self, to);
					low[v] = std::min(low[v], low[to]);
				} else {
					low[v] = std::min(low[v], ord[to]);
				}
			}
			if (low[v] == ord[v]) {
				while (true) {
					int u = visited.back();
					visited.pop_back();
					ord[u] = _n;
					ids[u] = group_num;
					if (u == v) break;
				}
				group_num++;
			}
		};
		for (int i = 0; i < _n; i++) {
			if (ord[i] == -1) dfs(dfs, i);
		}
		for (auto& x : ids) {
			x = group_num - 1 - x;
		}
		return {group_num, ids};
	}

	std::vector<std::vector<int>> scc() {
		auto ids = scc_ids();
		int group_num = ids.first;
		std::vector<int> counts(group_num);
		for (auto x : ids.second) counts[x]++;
		std::vector<std::vector<int>> groups(ids.first);
		for (int i = 0; i < group_num; i++) {
			groups[i].reserve(counts[i]);
		}
		for (int i = 0; i < _n; i++) {
			groups[ids.second[i]].push_back(i);
		}
		return groups;
	}

private:
	int _n;
	struct edge {
		int to;
	};
	std::vector<std::pair<int, edge>> edges;
};

}  // namespace atcoder

#endif  // ATCODER_INTERNAL_SCC_HPP

#ifndef ATCODER_TWOSAT_HPP
#define ATCODER_TWOSAT_HPP 1

namespace atcoder {

// Reference:
// B. Aspvall, M. Plass, and R. Tarjan,
// A Linear-Time Algorithm for Testing the Truth of Certain Quantified Boolean
// Formulas
struct two_sat {
public:
	two_sat() : _n(0), scc(0) {}
	explicit two_sat(int n) : _n(n), _answer(n), scc(2 * n) {}

	void add_clause(int i, bool f, int j, bool g) {
		assert(0 <= i && i < _n);
		assert(0 <= j && j < _n);
		scc.add_edge(2 * i + (f ? 0 : 1), 2 * j + (g ? 1 : 0));
		scc.add_edge(2 * j + (g ? 0 : 1), 2 * i + (f ? 1 : 0));
	}
	bool satisfiable() {
		auto id = scc.scc_ids().second;
		for (int i = 0; i < _n; i++) {
			if (id[2 * i] == id[2 * i + 1]) return false;
			_answer[i] = id[2 * i] < id[2 * i + 1];
		}
		return true;
	}
	std::vector<bool> answer() { return _answer; }

private:
	int _n;
	std::vector<bool> _answer;
	scc_graph scc;
};

}  // namespace atcoder

#endif  // ATCODER_TWOSAT_HPP