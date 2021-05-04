// const int ALPHABET_SIZE = 26;

// struct Vertex {
// 	int next[ALPHABET_SIZE];
// 	bool leaf = false;
// 	int p = -1;
// 	char pch;
// 	int link = -1;
// 	int go[ALPHABET_SIZE];

// 	Vertex(int p = -1, char ch = '$') : p(p), pch(ch) {
// 		memset(next, -1, ALPHABET_SIZE * sizeof(int));
// 		memset(go, -1, ALPHABET_SIZE * sizeof(int));
// 	}
// };

// struct AhoCorasick {
// 	vector<Vertex> trie(1);

// 	// adds a string of length K to the trie
// 	// Time: O(K)
// 	void insert(string const& s) {
// 		int v = 0;
// 		for (char ch : s) {
// 			int c = ch - 'a';
// 			if (trie[v].next[c] == -1) {
// 				trie[v].next[c] = trie.size();
// 				trie.emplace_back(v, ch);
// 			}
// 			v = trie[v].next[c];
// 		}
// 		trie[v].leaf = true;
// 	}

// 	int go(int v, char ch);


// 	int get_link(int v) {
// 		if (trie[v].link == -1) {
// 			if (v == 0 || trie[v].p == 0)
// 				trie[v].link = 0;
// 			else
// 				trie[v].link = go(get_link(trie[v].p), trie[v].pch);
// 		}
// 		return trie[v].link;
// 	}

// 	int go(int v, char ch) {
// 		int c = ch - 'a';
// 		if (trie[v].go[c] == -1) {
// 			if (trie[v].next[c] != -1)
// 				trie[v].go[c] = trie[v].next[c];
// 			else
// 				trie[v].go[c] = v == 0 ? 0 : go(get_link(v), ch);
// 		}
// 		return trie[v].go[c];
// 	}
// };

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