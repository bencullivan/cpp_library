#ifndef LOCAL_DBG
#define LOCAL_DBG 1

#include <cassert>
#include <cstddef>
#include <iostream>
#include <string>
#include <type_traits>
#include <utility>
#include <vector>

#include "colors.h"

namespace debug {

template <typename T, typename U>
std::ostream &operator<<(std::ostream &os, const std::pair<T, U> &p) {
    return os << "(" << p.first << ", " << p.second << ")";
}

template <typename T, typename U = typename std::enable_if<
                          !std::is_same<T, std::string>::value,
                          typename T::value_type>::type>
std::ostream &operator<<(std::ostream &os, const T &v) {
    os << "\n{";
    std::string sep = "";
    for (const U &x : v) {
        os << sep << x;
        sep = ", ";
    }
    return os << "}";
}

inline void print_vars() { std::cerr << std::endl; }

template <typename T, typename... U> void print_vars(T t, U... u) {
    std::cerr << t << (sizeof...(u) ? ", " : ""), print_vars(u...);
}

inline void fill_dimensions(std::vector<std::size_t> &dimensions) {}

template <typename T, typename... U>
void fill_dimensions(std::vector<std::size_t> &dimensions, T t, U... u) {
    assert(0 <= t);
    dimensions.push_back(t);
    fill_dimensions(dimensions, u...);
}

template <typename T>
void print_array(T x, std::size_t d,
                 const std::vector<std::size_t> &dimensions) {
    std::cerr << x;
}

template <typename T>
void print_array(T *a, std::size_t d,
                 const std::vector<std::size_t> &dimensions) {
    std::cerr << "\n{";
    std::string sep = "";
    for (std::size_t i = 0; i < dimensions[d]; i++) {
        std::cerr << sep;
        sep = ", ";
        print_array(a[i], d + 1, dimensions);
    }
    std::cerr << "}";
    if (d == 0) {
        std::cerr << std::endl;
    }
}

template <typename T>
void print_array(const std::vector<T> &a, std::size_t d,
                 const std::vector<std::size_t> &dimensions) {
    std::cerr << "\n{";
    std::string sep = "";
    for (std::size_t i = 0; i < dimensions[d]; i++) {
        std::cerr << sep, sep = ", ";
        if (d + 1 == dimensions.size()) {
            std::cerr << a[i];
        } else {
            print_array(a[i], d + 1, dimensions);
        }
    }
    std::cerr << "}";
    if (d == 0) {
        std::cerr << std::endl;
    }
}

} // namespace debug

#define dbg(...)                                                               \
    do {                                                                       \
        std::cerr << MAGENTA << __LINE__ << " [" << #__VA_ARGS__               \
                  << "]: " << GREEN;                                           \
        debug::print_vars(__VA_ARGS__);                                        \
        std::cerr << RESET << std::flush;                                      \
    } while (0)

#define dba(a, ...)                                                            \
    do {                                                                       \
        std::cerr << MAGENTA << __LINE__ << " [" << #a << "]: " << GREEN;      \
        std::vector<std::size_t> dimensions;                                   \
        debug::fill_dimensions(dimensions, __VA_ARGS__);                       \
        debug::print_array(a, 0, dimensions);                                  \
        std::cerr << RESET << std::flush;                                      \
    } while (0)

#endif // LOCAL_DBG