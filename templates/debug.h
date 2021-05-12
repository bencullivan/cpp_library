// This code is included in all the files that I compile with g++ to enable easy debugging.
// The bash compilation function that I use:
// function com() {
//     g++-10 -arch x86_64 -std=gnu++17 -O2 -Wall -include /Users/bencullivan/documents/CppLibrary/competition_templates/debug.h $1".cc" && ./a.out
// }
// ex:
// com normal

//#ifdef LOCAL
#ifndef LOL_DEBUG
#define LOL_DEBUG

#include <iostream>
#include <type_traits>
#include <utility>
#include <string>
#include <assert.h>

#ifndef _WIN32
#define RESET   "\033[0m"
#define GREEN   "\033[32m"
#define MAGENTA "\033[35m"
#else
#define RESET   ""
#define GREEN   ""
#define MAGENTA ""
#endif

// stl pair
template<typename K, typename V>
std::ostream& operator<<(std::ostream& os, const std::pair<K, V>& p) {
	return os << "(" << p.first << ", " << p.second << ")";
}

// any type of stl container
template<typename T_container, typename T = typename std::enable_if<!std::is_same<T_container, std::string>::value, typename T_container::value_type>::type>
std::ostream& operator<<(std::ostream &os, const T_container &v) {
	os << "\n{";
	std::string sep;
	for (const T &x : v) {
		os << sep << x;
		sep = ", ";
	}
	return os << '}';
}

void debug_helper() {
	std::cout << RESET << std::endl;
}

template<typename Head, typename... Tail>
void debug_helper(Head H, Tail... T) {
	std::cout << H;
	if (sizeof...(T)) {
		std::cout << ", "; 
	}
	debug_helper(T...);
}

#define dbg(...) std::cout << MAGENTA << __LINE__ << " [" << #__VA_ARGS__ << "]: " << GREEN, debug_helper(__VA_ARGS__)

// 1d array
#define dba1(_arr,_d1) { \
	std::cout << MAGENTA << __LINE__ << " [" << #_arr << "]:" << GREEN << "\n{"; \
	for (long long _i = 0; _i < _d1; _i++) { \
		std::cout << _arr[_i]; \
		if (_i < _d1-1) std::cout << ", "; \
	} \
	std::cout << "}" << RESET << endl; }

// 2d array
#define dba2(_arr,_d1,_d2) { \
	std::cout << MAGENTA << __LINE__ << " [" << #_arr << "]:" << GREEN << "\n{"; \
	for (long long _i = 0; _i < _d1; _i++) { \
		std::cout << "\n{"; \
		for (long long _j = 0; _j < _d2; _j++) { \
			std::cout << _arr[_i][_j]; \
			if (_j < _d2-1) std::cout << ", "; \
		} \
		std::cout << "},"; \
	} \
	std::cout << "}" << RESET << std::endl; }

// 3d array
#define dba3(_arr,_d1,_d2,_d3) { \
	std::cout << MAGENTA << __LINE__ << " [" << #_arr << "]:" << GREEN << "\n{"; \
	for (long long _i = 0; _i < _d1; _i++) { \
		std::cout << "\n{"; \
		for (long long _j = 0; _j < _d2; _j++) { \
			std::cout << "{"; \
			for (long long _k = 0; _k < _d3; _k++) { \
				std::cout << _arr[_i][_j][_k]; \
				if (_k < _d3-1) std::cout << ", "; \
			} \
			std::cout << "}"; \
			if (_j < _d2-1) std::cout << ", "; \
		} \
		std::cout << "},"; \
	} \
	std::cout << "}" << RESET << std::endl; }

// 4d array
#define dba4(_arr,_d1,_d2,_d3,_d4) { \
	std::cout << MAGENTA << __LINE__ << " [" << #_arr << "]:" << GREEN << "\n{"; \
	for (long long _i = 0; _i < _d1; _i++) { \
		std::cout << "\n{"; \
		for (long long _j = 0; _j < _d2; _j++) { \
			std::cout << "\n{"; \
			for (long long _k = 0; _k < _d3; _k++) { \
				std::cout << "{"; \
				for (long long _l = 0; _l < _d4; _l++) { \
					std::cout << _arr[_i][_j][_k][_l]; \
					if (_l < _d4-1) std::cout << ", "; \
				} \
				std::cout << "}"; \
				if (_k < _d3-1) std::cout << ", "; \
			} \
			std::cout << "},"; \
		} \
		std::cout << "},"; \
	} \
	std::cout << "}" << RESET << std::endl; }

#endif // LOL_DEBUG
//#endif // LOCAL