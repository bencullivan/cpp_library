struct AhoCorasick {
	static constexpr int alpha = 26; // change
	static constexpr char base_ch = 'a'; // change

	struct Node {
		int ch[alpha];  // the edges to child nodes
		int par;        // the index of the parent node
		int pch;        // the char of the edge from the parent to the current node
		int sl = 0;     // the suffix link to the node whose path is the longest path that is a suffix of the current path
		int el = 0;     // the link to the leaf node of the longest word that can be made from a suffix of the current path
		int id = -1;    // if a word ends at this node its id, else -1
		Node(int _par, int _pch) : par(_par), pch(_pch) {
			memset(ch, -1, alpha * sizeof(int));
		}
	};

	vector<Node> data; // the trie
	vector<int> lengths;  // the lengths of the words in the dictionary
	vector<vector<int>> duplicates; // use if duplicates are allowed

	AhoCorasick() : data(1, Node(0, 0)) {}

	void reserve(int n) {
		lengths.reserve(n);
		duplicates.reserve(n);
	}

	void insert(string& s, int idx) {
		int cur = 0;
		for (int i = 0; i < (int)s.size(); i++) {
			int c = s[i] - base_ch;
			if (data[cur].ch[c] == -1) {
				data[cur].ch[c] = data.size();
				data.emplace_back(cur, c);
			}
			cur = data[cur].ch[c];
		}
		duplicates.emplace_back();
		lengths.push_back(s.size());
		if (data[cur].id != -1) duplicates[data[cur].id].push_back(idx);
		else data[cur].id = idx;
	}

	// call after inserting all words into the trie
	void build() {
		data[0].sl = 0; // the root is linked to itself
		data[0].el = 0;
		queue<int> q;
		q.push(0);
		while (q.size() && data[q.front()].par == 0) { // process the root and its children
			int cur = q.front();
			q.pop();
			if (data[cur].id != -1) data[cur].el = cur;
			for (int i = 0; i < alpha; i++) {
				if (data[cur].ch[i] != -1) q.push(data[cur].ch[i]);
			}
		}
		while (q.size()) {
			int cur = q.front();
			q.pop();
			int link = data[data[cur].par].sl; // initialize the suffix link to the suffix link of the parent node
			int c = data[cur].pch; // the character on the edge from the parent node to the current node
			while (data[link].ch[c] == -1 && link > 0) { // backtrack until we find a path that has c as a child or we reach the root
				link = data[link].sl;
			}
			if (data[link].ch[c] != -1) { // we have found a node that has c as a child
				data[cur].sl = data[link].ch[c]; // set the child node as the suffix link of the current node
			}
			if (data[cur].id != -1) { // a word ends at the current node so it is its own end word link
				data[cur].el = cur;
			}
			else { // there is no word that ends at the current node so its end word link is the end word link of its suffix link node
				data[cur].el = data[data[cur].sl].el;
			}
			for (int i = 0; i < alpha; i++) { // bfs on all children
				if (data[cur].ch[i] != -1) q.push(data[cur].ch[i]);
			}
		}
	}

	// process a text to find where dictionary words occur in it
	template<typename F> // function op(id, i) where id is the id of the string that occurs and i is the index in t MUST BE O(1)
	void process(string &t, F &&op) {
		int cur = 0; // we begin at the root
		for (int i = 0; i < (int)t.size(); i++) {
			int c = t[i]-base_ch;
			while (data[cur].ch[c] == -1 && cur > 0) { // backtrack until we find a path that has c as a child or we reach the root
				cur = data[cur].sl;
			}
			if (data[cur].ch[c] != -1) { // if we have found a path, move forward
				cur = data[cur].ch[c];
			}
			int end = data[cur].el; // we will now process all the words that are suffixes of the current path
			while (end > 0) {
				op(data[end].id, i); 
				end = data[data[end].sl].el;
			}
		}
	}
}; // AhoCorasick