template<typename T> 
struct Chash {
	const T RANDOM = (ll)(make_unique<char>().get()) ^ chrono::high_resolution_clock::now().time_since_epoch().count();
	static ull hash_f(ull x) { 
		// http://xorshift.di.unimi.it/splitmix64.c
		x += 0x9e3779b97f4a7c15;
		x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
		x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
		return x ^ (x >> 31);
	}
	static unsigned hash_combine(unsigned a, unsigned b) {
		return a * 31 + b;
	}
	T operator()(T x) const {
		return hash_f(x) ^ RANDOM;
	}
};