#include <iostream>
#include <string>
#include <utility>
#include <type_traits>

using namespace std;

#define GREEN "\033[32m"
#define MAGENTA "\033[35m"
#define RESET "\033[0m"
template<typename T, typename U>
ostream& operator << (ostream& os, const pair<T, U>& p) {
  return os << "(" << p.first << ", " << p.second << ")";
}
template<typename T, typename U = typename 
  enable_if<!is_same<T, string>::value, typename T::value_type>::type>
ostream& operator << (ostream& os, const T& v) {
  os << "\n{";
  string sep = "";
  for (const U& x:v) os << sep << x, sep = ", ";
  return os << "}";
}
void _dbg() {
  cerr << RESET << endl;
}
template<typename T, typename... U>
void _dbg(T t, U... u) {
  cerr << t << (sizeof...(u) ? ", " : ""), _dbg(u...);
}
int _dm[10], _mx;
void _dbf() {}
template<typename T, typename... U>
void _dbf(T t, U... u) {
  _dm[_mx++] = t, _dbf(u...);
}
template<typename T>
void _dba(T x, int d) {
  cerr << x;
}
template<typename T>
void _dba(T* a, int d) {
  cerr << "\n{";
  string sep = "";
  for (int i = 0; i < _dm[d]; i++) cerr << sep, sep = ", ", _dba(a[i], d + 1);
  cerr << "}" << (d == 0 ? RESET : "") << endl;
}
#define dbg(...) cerr << MAGENTA << __LINE__ << " [" << #__VA_ARGS__ << "]: " \
  << GREEN, _dbg(__VA_ARGS__)
#define dba(a,...) cerr << MAGENTA << __LINE__ << " [" << #a << "]: " \
  << GREEN, _mx = 0, _dbf(__VA_ARGS__), _dba(a, 0)
