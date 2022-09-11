#ifndef DEBUG_COLORS
#define DEBUG_COLORS 1

#ifdef _WIN32
#include <windows.h>

#define GREEN 10
#define MAGENTA 13
#define WHITE 15
namespace DebugColors
{
    bool _debug_color_handle_set = false;
    HANDLE _debug_color_hErr;
}
#define set_color(color_code)                                                \
    do                                                                       \
    {                                                                        \
        if (!DebugColors::_debug_color_handle_set)                           \
        {                                                                    \
            DebugColors::_debug_color_hErr = GetStdHandle(STD_ERROR_HANDLE); \
            DebugColors::_debug_color_handle_set = true;                     \
        }                                                                    \
        SetConsoleTextAttribute(DebugColors::_debug_color_hErr, color_code); \
    } while (0)
#define reset_color set_color(WHITE)

#else

// source: https://stackoverflow.com/questions/9158150/colored-output-in-c/9158263
// the following are UBUNTU/LINUX and MacOS terminal color codes
#define GREEN "\033[32m"
#define MAGENTA "\033[35m"
#define RESET "\033[0m"
#define set_color(color_code) std::cerr << color_code
#define reset_color set_color(RESET)

#endif // _WIN32

#endif // DEBUG_COLORS