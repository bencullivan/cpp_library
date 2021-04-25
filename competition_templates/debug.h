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

// the following are UBUNTU/LINUX, and MacOS ONLY terminal color codes.
// Source: https://stackoverflow.com/questions/9158150/colored-output-in-c/9158263
#define RESET   "\033[0m"
#define BLACK   "\033[30m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define BLUE    "\033[34m"
#define MAGENTA "\033[35m"
#define CYAN    "\033[36m"
#define WHITE   "\033[37m"
#define BOLDBLACK   "\033[1m\033[30m"
#define BOLDRED     "\033[1m\033[31m"
#define BOLDGREEN   "\033[1m\033[32m"
#define BOLDYELLOW  "\033[1m\033[33m"
#define BOLDBLUE    "\033[1m\033[34m"
#define BOLDMAGENTA "\033[1m\033[35m"
#define BOLDCYAN    "\033[1m\033[36m"
#define BOLDWHITE   "\033[1m\033[37m"

// stl pair
template<typename K, typename V>
std::ostream& operator<<(std::ostream& os, const std::pair<K, V>& p) {
    return os << "(" << p.first << ", " << p.second << ")";
}

// any type of stl container
// Source: neal
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
    std::cerr << RESET << std::endl;
}

template<typename Head, typename... Tail>
void debug_helper(Head H, Tail... T) {
    std::cerr << H;
    if (sizeof...(T)) {
        std::cerr << ", "; 
    }
    debug_helper(T...);
}

// Source: neal
#define dbg(...) std::cerr << MAGENTA << __LINE__ << " [" << #__VA_ARGS__ << "]: " << GREEN, debug_helper(__VA_ARGS__)

// Array output

long long _n_dims = 0;
long long _arr_dims[10];

void fill_arr_dims() {}

template<typename Head, typename... Tail>
void fill_arr_dims(Head H, Tail... T) {
    _arr_dims[_n_dims++] = (long long) H;
    fill_arr_dims(T...);
}

// 1d array
#define dba1(_arr,...) { \
    std::cerr << MAGENTA << __LINE__ << " [" << #_arr << "]:" << GREEN << "\n{"; _n_dims = 0; fill_arr_dims(__VA_ARGS__); \
    for (long long _i = 0; _i < _arr_dims[0]; _i++) { \
        std::cerr << _arr[_i]; \
        if (_i < _arr_dims[0]-1) std::cerr << ", "; \
    } \
    std::cerr << "}" << RESET << endl; }

// 2d array
#define dba2(_arr,...) { \
    std::cerr << MAGENTA << __LINE__ << " [" << #_arr << "]:" << GREEN << "\n{"; _n_dims = 0; fill_arr_dims(__VA_ARGS__); \
    for (long long _i = 0; _i < _arr_dims[0]; _i++) { \
        std::cerr << "\n{"; \
        for (long long _j = 0; _j < _arr_dims[1]; _j++) { \
            std::cerr << _arr[_i][_j]; \
            if (_j < _arr_dims[1]-1) std::cerr << ", "; \
        } \
        std::cerr << "},"; \
    } \
    std::cerr << "}" << RESET << std::endl; }

// 3d array
#define dba3(_arr,...) { \
    std::cerr << MAGENTA << __LINE__ << " [" << #_arr << "]:" << GREEN << "\n{"; _n_dims = 0; fill_arr_dims(__VA_ARGS__); \
    for (long long _i = 0; _i < _arr_dims[0]; _i++) { \
        std::cerr << "\n{"; \
        for (long long _j = 0; _j < _arr_dims[1]; _j++) { \
            std::cerr << "{"; \
            for (long long _k = 0; _k < _arr_dims[2]; _k++) { \
                std::cerr << _arr[_i][_j][_k]; \
                if (_k < _arr_dims[2]-1) std::cerr << ", "; \
            } \
            std::cerr << "}"; \
            if (_j < _arr_dims[1]-1) std::cerr << ", "; \
        } \
        std::cerr << "},"; \
    } \
    std::cerr << "}" << RESET << std::endl; }

// 4d array
#define dba4(_arr,...) { \
    std::cerr << MAGENTA << __LINE__ << " [" << #_arr << "]:" << GREEN << "\n{"; _n_dims = 0; fill_arr_dims(__VA_ARGS__); \
    for (long long _i = 0; _i < _arr_dims[0]; _i++) { \
        std::cerr << "\n{"; \
        for (long long _j = 0; _j < _arr_dims[1]; _j++) { \
            std::cerr << "\n{"; \
            for (long long _k = 0; _k < _arr_dims[2]; _k++) { \
                std::cerr << "{"; \
                for (long long _l = 0; _l < _arr_dims[3]; _l++) { \
                    std::cerr << _arr[_i][_j][_k][_l]; \
                    if (_l < _arr_dims[3]-1) std::cerr << ", "; \
                } \
                std::cerr << "}"; \
                if (_k < _arr_dims[2]-1) std::cerr << ", "; \
            } \
            std::cerr << "},"; \
        } \
        std::cerr << "},"; \
    } \
    std::cerr << "}" << RESET << std::endl; }

#endif // LOL_DEBUG
//#endif // LOCAL