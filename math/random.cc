mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());
mt19937_64 rngll(chrono::high_resolution_clock::now().time_since_epoch().count());
inline int urand(int l, int r) { return uniform_int_distribution<int>(l, r)(rng); }
inline long long urandll(long long l, long long r) { return uniform_int_distribution<long long>(l, r)(rngll); }