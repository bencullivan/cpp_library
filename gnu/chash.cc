#include <ext/pb_ds/assoc_container.hpp>
// https://gist.github.com/Chillee/3bd6ee4429abb4a2e7c19959fb1490ae#file-hash-table-cpp
template <typename T> struct chash {
  const T RANDOM =
      (long long)(std::make_unique<char>().get()) ^
      std::chrono::high_resolution_clock::now().time_since_epoch().count();
  static unsigned long long hash_f(unsigned long long x) {
    // http://xorshift.di.unimi.it/splitmix64.c
    x += 0x9e3779b97f4a7c15;
    x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
    x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
    return x ^ (x >> 31);
  }
  static unsigned hash_combine(unsigned a, unsigned b) { return a * 31 + b; }
  T operator()(T x) const { return hash_f(x) ^ RANDOM; }
};
template <typename K, typename V, typename Hash = chash<K>>
using hmap = __gnu_pbds::gp_hash_table<K, V, Hash>;
template <typename K, typename Hash = chash<K>>
using hset = hmap<K, __gnu_pbds::null_type, Hash>;