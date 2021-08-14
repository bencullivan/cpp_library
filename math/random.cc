mt19937 rng(chrono::high_resolution_clock::now().time_since_epoch().count());
mt19937_64 rngll(chrono::high_resolution_clock::now().time_since_epoch().count());
int urand(int l, int r) {
  return uniform_int_distribution<int>(l, r)(rng);
}
ll urandll(ll l, ll r) {
  return uniform_int_distribution<ll>(l, r)(rngll);
}