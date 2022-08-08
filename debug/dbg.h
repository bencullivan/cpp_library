#ifndef LOCAL_DBG
#define LOCAL_DBG 1
#include <iostream>
#include <string>
#include <utility>
#include <type_traits>
#include <vector>
#include "./colors.h"
namespace debug {
template<typename T, typename U>
std::ostream& operator << (std::ostream& os, const std::pair<T, U>& p) {
	return os << "(" << p.first << ", " << p.second << ")";
}
template<typename T, typename U = typename std::enable_if<!std::is_same<T, std::string>::value, typename T::value_type>::type>
std::ostream& operator << (std::ostream& os, const T& v) {
	os << "\n{";
	std::string sep = "";
	for (const U& x:v) os << sep << x, sep = ", ";
	return os << "}";
}
void print_var() {
	std::cerr << RESET << std::endl;
}
template<typename T, typename... U>
void print_var(T t, U... u) {
	std::cerr << t << (sizeof...(u) ? ", " : ""), print_var(u...);
}
int dimensions[10], n_dimensions;
void fill_dimensions() {}
template<typename T, typename... U>
void fill_dimensions(T t, U... u) {
	dimensions[n_dimensions++] = t, fill_dimensions(u...);
}
template<typename T>
void print_array(T x, int d) {
	std::cerr << x;
}
template<typename T>
void print_array(T* a, int d) {
	std::cerr << "\n{";
	std::string sep = "";
	for (int i = 0; i < dimensions[d]; i++) std::cerr << sep, sep = ", ", print_array(a[i], d + 1);
	std::cerr << "}";
	if (d == 0) std::cerr << RESET << std::endl;
}
template<typename T>
void print_array(const std::vector<T>& a, int d) {
	std::cerr << "\n{";
	std::string sep = "";
	for (int i = 0; i < dimensions[d]; i++) {
		std::cerr << sep, sep = ", ";
		if (d == n_dimensions - 1) std::cerr << a[i];
		else print_array(a[i], d + 1);
	}
	std::cerr << "}";
	if (d == 0) std::cerr << RESET << std::endl;
}
} // namespace debug
#define dbg(...) std::cerr << MAGENTA << __LINE__ << " [" << #__VA_ARGS__ << "]: " \
	<< GREEN, debug::print_var(__VA_ARGS__)
#define dba(a, ...) std::cerr << MAGENTA << __LINE__ << " [" << #a << "]: " << GREEN, \
	debug::n_dimensions = 0, debug::fill_dimensions(__VA_ARGS__), debug::print_array(a, 0)
#endif // LOCAL_DBG