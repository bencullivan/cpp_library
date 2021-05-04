struct Trie {
	static constexpr int alpha = 26; // change
	static constexpr char base_ch = 'a'; // change

	struct Node {
		int ch[alpha];
		bool leaf;
		Node() {
			memset(ch, -1, alpha * sizeof(int));
			leaf = false;
		}
	};

	vector<Node> data(1);

	void insert(string& s) {
		int cur = 0;
		for (int i = 0; i < (int)s.size(); i++) {
			if (data[cur].ch[s[i]-base_ch] == -1) {
				data[cur].ch[s[i]-base_ch] = (int)data.size();
				data.emplace_back();
			}
			cur = data[cur].ch[s[i]-base_ch];
		}
		data[cur].leaf = true;
	}
}; // Trie