// This code is included in all the files that I compile with g++ to enable easy debugging.
// The compilation function that I use:
// function com() {
//     g++-10 -arch x86_64 -std=gnu++17 -O2 -Wall -include /Users/bencullivan/documents/CppLibrary/competition_templates/debug.h $1".cc" && ./a.out
// }
// ex:
// com normal


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
// Source: neal (cf)
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

/*
template<typename T> void debug_container(std::string name, T begin, T end, int line_num) {
    std::cerr << line_num << ": " << name << " = {";
    while (begin != end) {
        std::cerr << (*begin);
        ++begin;
        if (begin != end) {
            std::cerr << ", ";
        }
    }
    std::cerr << "}" << std::endl;
}
*/


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

// Source: neal (cf)
#define dbg(...) std::cerr << GREEN << __LINE__ << " [" << #__VA_ARGS__ << "]: ", debug_helper(__VA_ARGS__)
//#define dbc(container) debug_container(#container, (container).begin(), (container).end(), __LINE__)
//#define dbci(star,ende) debug_container(#star, star, ende, __LINE__)


//#ifndef LOL_DEBUG
#endif