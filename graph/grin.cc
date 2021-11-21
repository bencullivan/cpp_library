vector<vector<int>> grin(int n, int m, bool directed = false) {
	vector<vector<int>> graph(n+1);
	for (int i = 0; i < m; i++) {
		int a, b;
		cin >> a >> b;
		graph[a].push_back(b);
		if (!directed) {
			graph[b].push_back(a);
		}
	}
	return graph;
}
vector<vector<pair<long long, long long>>> wgrin(int n, int m, bool directed = false) {
	vector<vector<pair<long long, long long>>> graph(n+1);
	for (int i = 0; i < m; i++) {
		ll a, b, c;
		cin >> a >> b >> c;
		graph[a].emplace_back(b, c);
		if (!directed) {
			graph[b].emplace_back(a, c);
		}
	}
	return graph;
}