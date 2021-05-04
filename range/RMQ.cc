/**
 * Author: Johan Sannemo, pajenegod
 * Date: 2015-02-06
 * License: CC0
 * Source: Folklore
 * Description: Range Minimum Queries on an array. Returns
 * min(V[a], V[a + 1], ... V[b - 1]) in constant time.
 * Usage:
 *  RMQ rmq(values);
 *  rmq.query(inclusive, exclusive);
 * Time: $O(|V| \log |V| + Q)$
 * Status: stress-tested
 */
#define query_op min
template<class T>
struct RMQ {
	vector<vector<T>> jmp;
	RMQ(const vector<T>& V) : jmp(1, V) {
		for (int pw = 1, k = 1; pw * 2 <= sz(V); pw *= 2, ++k) {
			jmp.emplace_back((int)V.size() - pw * 2 + 1);
			for (int j = 0; j < (int)jmp[k].size(); j++)
				jmp[k][j] = query_op(jmp[k - 1][j], jmp[k - 1][j + pw]);
		}
	}
	// gets the minimum of the range [a, b)
	T get(int a, int b) {
		assert(a < b); // or return inf if a == b
		int dep = 31 - __builtin_clz(b - a);
		return query_op(jmp[dep][a], jmp[dep][b - (1 << dep)]);
	}
};
#undef query_op