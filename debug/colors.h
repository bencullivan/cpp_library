#ifndef DEBUG_COLORS
#define DEBUG_COLORS 1

// source: https://stackoverflow.com/questions/9158150/colored-output-in-c/9158263
// the following are UBUNTU/LINUX and MacOS terminal color codes
#define GREEN "\033[32m"
#define MAGENTA "\033[35m"
#define RESET "\033[0m"
#define set_color(color_code) std::cerr << color_code
#define reset_color set_color(RESET)

#endif // DEBUG_COLORS