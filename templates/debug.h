// This code is included in all the files that I compile with g++ to enable easy debugging.
// The bash compilation function that I use:
// function com() {
//     g++-10 -arch x86_64 -std=gnu++17 -O2 -Wall -D LOCAL=1 -D LOL_DEBUG=1 -include /Users/bencullivan/documents/CppLibrary/templates/debug.h $1".cc" && ./a.out
// }
// ex:
// com normal

#include <iostream>
#include <type_traits>
#include <utility>
#include <string>

#ifndef _WIN32
#define RESET "\033[0m"
#define GREEN "\033[32m"
#define MAGENTA "\033[35m"
#else
#define RESET ""
#define GREEN ""
#define MAGENTA ""
#endif

// stl pair
template<typename K, typename V>
std::ostream& operator<<(std::ostream& os, const std::pair<K, V>& p)
{
  return os << "(" << p.first << ", " << p.second << ")";
}
// any type of stl container
template<typename T_container, typename T = typename std::enable_if<!std::is_same<T_container, std::string>::value, typename T_container::value_type>::type>
std::ostream& operator<<(std::ostream &os, const T_container &v)
{
  os << "\n{";
  std::string sep;
  for (const T &x : v) {
    os << sep << x;
    sep = ", ";
  }
  return os << '}';
}
void debug_helper()
{
  std::cout << RESET << std::endl;
}
template<typename Head, typename... Tail>
void debug_helper(Head H, Tail... T)
{
  std::cout << H;
  if (sizeof...(T)) {
    std::cout << ", "; 
  }
  debug_helper(T...);
}
#define dbg(...) std::cout << MAGENTA << __LINE__ << " [" << #__VA_ARGS__ << "]: " << GREEN, debug_helper(__VA_ARGS__)
// debugging C-style arrays of variable size
int debug_arr_dims[10], debug_max_dim;
void debug_fill_arr_dims()
{
}
template<typename Head, typename... Tail>
void debug_fill_arr_dims(Head H, Tail... T)
{
  debug_arr_dims[debug_max_dim++] = H;
  debug_fill_arr_dims(T...);
}
template<typename T>
void debug_arr(T elt, int d)
{
  std::cout << elt;
}
template<typename T>
void debug_arr(T* arr, int d)
{
  std::cout << "\n{";
  std::string sep;
  for (int i = 0; i < debug_arr_dims[d]; i++) {
    std::cout << sep;
    sep = ", ";
    debug_arr(arr[i], d + 1);
  }
  std::cout << '}';
  if (d == 0) std::cout << RESET << std::endl;
}
#define dba(arr,...) std::cout << MAGENTA << __LINE__ << " [" << #arr << "]: " << GREEN, debug_max_dim = 0, debug_fill_arr_dims(__VA_ARGS__), debug_arr(arr, 0)